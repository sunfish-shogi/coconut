//
//  GestureLayer.cpp
//
//  Created by Kubo Ryosuke on 13/09/03.
//
//

#include "GestureLayer.h"
#include <sstream>

USING_NS_CC;

namespace {
	
	uint64_t currentMillisec() {
		struct timeval cur;
		gettimeofday(&cur, NULL);
		return ((uint64_t)cur.tv_sec * 1000 + cur.tv_usec / 1000);
	}
	
}

namespace coconut {

	GestureLayer::GestureLayer() {
		_tapAllowableError = 5.0f;
		
		_enableDoubleTap = false;
		_doubleTapTimeThreshold = 300L;
		
		_enableLongTouch = false;
		_longTouchTimeThreshold = 1000L;
		
		_longTapTimeThreshold = 1000L;
		
		_flickAreaType = AreaType::ELLIPSE;
		_flickXThreshold = 500.0f;
		_flickYThreshold = 500.0f;
		_flickLifeSpan = 200;
		
		_swipeAreaType = AreaType::ELLIPSE;
		_swipeXThreshold = 30.0f;
		_swipeYThreshold = 30.0f;
		
		_largeVelocityTime = 0;
		_tapOk = false;
		_prevTapTime = 0;
		_swipeOk = false;
	}
	
	GestureLayer::~GestureLayer() {
	}
	
	bool GestureLayer::init() {
		if (!Layer::init()) {
			return false;
		}
		
		setTouchEnabled(true);
		setTouchMode(Touch::DispatchMode::ALL_AT_ONCE); // default
		
		return true;
	}
	
	Point GestureLayer::t2p(Touch* touch) {
		const Point& point = Director::getInstance()->convertToUI(touch->getLocationInView());
		return convertToNodeSpace(point);
	}
	
	int GestureLayer::touchOpen(const std::vector<Touch*>& touches) {
		int count = 0;
		uint64_t currTime = currentMillisec();
		for (auto it = touches.begin(); it != touches.end();) {
			Touch* touch = (Touch*)*(it++);
			for (auto ih = _touchHistories.begin(); ih != _touchHistories.end(); ih++) {
				if (touch->getID() == (*ih).id) {
					//CCASSERT(false, String::createWithFormat("touch id %d already exists.", touch->getID())->getCString());
					_touchHistories.erase(ih);
					break;
				}
			}
			Point point = t2p(touch);
			if (fgTouchBegan(point) == GestureResult::OK) {
				TouchHistory th;
				th.id = touch->getID();
				th.start = point;
				th.startTime = currTime;
				th.curr = point;
				th.currTime = currTime;
				_touchHistories.push_back(th);
				count++;
			}
		}
		
		_largeVelocityTime = 0;
		return count;
	}
	
	void GestureLayer::touchNext(const std::vector<Touch*>& touches) {
		uint64_t currTime = currentMillisec();
		for (auto ih = _touchHistories.begin(); ih != _touchHistories.end(); ih++) {
			TouchHistory& th = *ih;
			th.prev = th.curr;
			th.prevTime = th.currTime;
			th.currTime = currTime;
			auto it = touches.begin();
			for (; it != touches.end(); it++) {
				Touch* touch = (Touch*)*it;
				if (touch->getID() == (*ih).id) {
					th.curr = t2p(touch);
					break;
				}
			}
		}
	}
	
	void GestureLayer::touchClose(const std::vector<Touch*>& touches, std::vector<TouchHistory>* ths) {
		for (auto it = touches.begin(); it != touches.end(); it++) {
			Touch* touch = (Touch*)*it;
			for (auto ih = _touchHistories.begin(); ih != _touchHistories.end(); ih++) {
				if (touch->getID() == (*ih).id) {
					if (ths != nullptr) {
						ths->push_back(*ih);
					}
					_touchHistories.erase(ih);
					break;
				}
			}
		}
	}
	
  bool GestureLayer::onTouchBegan(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		return touchesBegan(touches);
	}
	
  void GestureLayer::onTouchMoved(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		touchesMoved(touches);
	}
	
  void GestureLayer::onTouchEnded(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		touchesEnded(touches);
	}
	
	void GestureLayer::onTouchCancelled(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		touchesCancelled(touches);
	}
	
	void GestureLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesBegan(touches);
	}
		
	void GestureLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesMoved(touches);
	}
	
	void GestureLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesEnded(touches);
	}
	
	void GestureLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesCancelled(touches);
	}
	
	bool GestureLayer::touchesBegan(const std::vector<Touch*>& touches) {
		int count = touchOpen(touches);
		
		// scheduler
		unscheduleLongTouch();
		unscheduleSingleTap();
		
		_tapOk = true;
		_swipeOk = true;

		if (_touchHistories.size() == 1) {
			// single touch
			const TouchHistory& th = _touchHistories[0];
			
			if (fgTouch(th.curr) == GestureResult::OK) {
				_tapOk = false;
				return true;
			}
			
			scheduleLongTouch();
		}
		return count != 0;
	}
	
	void GestureLayer::touchesMoved(const std::vector<Touch*>& touches) {
		touchNext(touches);
		
		if (_touchHistories.size() == 1) {
			// single touch
			const TouchHistory& th = _touchHistories[0];
			
			// tap
			Point dsum = th.curr - th.start;
			updateTap(dsum);
			
			// flick
			Point delta = th.curr - th.prev;
			uint64_t deltaTime = th.currTime - th.prevTime;
			updateLargeVelocity(delta, deltaTime);
			if (checkFlick() &&
					fgFlick(th.start, _largeVelocity) == GestureResult::OK) {
				_swipeOk = false;
				return;
			}
			
			// swipe
			if (checkSwipe(dsum) &&
					fgSwipe(th.start, dsum) == GestureResult::OK) {
				_swipeOk = false;
				return;
			}
			
			// movement
			fgMove(th.curr);
			fgMove(th.prev, delta);
			
		} else if (_touchHistories.size() == 2) {
			// double touch
			TouchHistory th1 = _touchHistories[0];
			TouchHistory th2 = _touchHistories[1];
			
			// pinch
			Point prevMiddle = th1.prev.getMidpoint(th2.prev);
			float prevMagunitude = th1.prev.getDistance(th2.prev);
			float currMagunitude = th1.curr.getDistance(th2.curr);
			float scale = currMagunitude == 0.0f || prevMagunitude == 0.0f
										? 1.0f :currMagunitude / prevMagunitude;
			fgPinch(prevMiddle, scale);
	
			// movement
			Point currMiddle = th1.curr.getMidpoint(th2.curr);
			Point delta = currMiddle - prevMiddle;
			float prevRotation = -angleAsRadian(th1.prev, th2.prev) * (float)(180.0 / M_PI);
			float currRotation = -angleAsRadian(th1.curr, th2.curr) * (float)(180.0 / M_PI);
			float deltaRotation = currRotation - prevRotation;
			if (deltaRotation > 180.0f) { deltaRotation -= 180.0f * 2; }
			if (deltaRotation < -180.0f) { deltaRotation += 180.0f * 2; }
			fgMove(currMiddle, currRotation);
			fgMove(prevMiddle, delta, deltaRotation);
		}
	}
	
	void GestureLayer::touchesEnded(const std::vector<Touch*>& touches) {
		std::vector<TouchHistory> ths;
		touchClose(touches, &ths);
		
		// scheduler
		unscheduleLongTouch();
		unscheduleSingleTap();
		
		// single touch
		if (_touchHistories.size() == 0 && ths.size() == 1) {
			TouchHistory& th = ths[0];
			
			// double tap
			if (checkDoubleTap(th.startTime) &&
					fgDoubleTap(th.start) == GestureResult::OK) {
				unscheduleSingleTap();
				_prevTapTime = 0;
				return;
			}
			
			// long tap
			if (checkLongTap(th.startTime)) {
				_prevTapTime = th.startTime;
				if (fgLongTap(th.start) == GestureResult::OK) {
					return;
				}
			}
			
			// tap
			if (checkTap()) {
				_prevTap = th.start;
				_prevTapTime = th.startTime;
				if (_enableDoubleTap) {
					scheduleSingleTap();
				} else {
					if (fgTap(th.start) == GestureResult::OK) {
						return;
					}
				}
			}
			
			// flick
			if (checkFlick() &&
					fgFlickWithDetouch(th.start, _largeVelocity) == GestureResult::OK) {
				return;
			}
			
			// swipe
			Point dsum = th.curr - th.start;
			if (checkSwipe(dsum) &&
					fgSwipeWithDetouch(th.start, dsum) == GestureResult::OK) {
				return;
			}
			
			fgDetouch(th.curr);
		}
	}
	
	void GestureLayer::touchesCancelled(const std::vector<Touch*>& touches) {
		touchClose(touches);
	}
		
	void GestureLayer::updateLargeVelocity(const Point& delta, long deltaTime) {
		Point velocity = Point(delta.x * 1000.0f / deltaTime,
													 delta.y * 1000.0f / deltaTime);
		if (isOutsidOfArea(velocity, _flickAreaType, _flickXThreshold, _flickYThreshold)) {
			_largeVelocity = velocity;
			_largeVelocityTime = currentMillisec();
		} else if (delta.dot(_largeVelocity) < 0.0f) {
			_largeVelocityTime = 0;
		}
	}
	
	void GestureLayer::updateTap(const Point& dsum) {
		if (_tapOk && dsum.getLength() >= _tapAllowableError) {
			_tapOk = false;
			unscheduleLongTouch();
			unscheduleSingleTap();
		}
	}
		
	bool GestureLayer::checkDoubleTap(uint64_t startTime) {
		return _enableDoubleTap && _tapOk &&
				startTime - _prevTapTime <= _doubleTapTimeThreshold;
	}
		
	bool GestureLayer::checkLongTap(uint64_t startTime) {
		return _tapOk && (currentMillisec() - startTime >= _longTapTimeThreshold);
	}
		
	bool GestureLayer::checkTap() {
		return _tapOk;
	}
		
	bool GestureLayer::checkFlick() {
		if (_swipeOk && _largeVelocityTime != 0) {
			if (_flickLifeSpan == 0) {
				return true;
			}
			uint64_t age = currentMillisec() - _largeVelocityTime;
			if (age < _flickLifeSpan) {
				return true;
			}
		}
		return false;
	}
	
	bool GestureLayer::checkSwipe(const Point& d) {
		return _swipeOk && isOutsidOfArea(d, _swipeAreaType, _swipeXThreshold, _swipeYThreshold);
	}
	
	bool GestureLayer::isOutsidOfArea(const Point& v, AreaType areaType, float areaX, float areaY) {
		if (areaType == AreaType::RECTANGLE) {
			return fabsf(v.x) >= areaX || fabsf(v.y) >= areaY;
		} else if (areaType == AreaType::ELLIPSE) {
			return Point(v.x, v.y * areaX / areaY).getLengthSq() >= areaX * areaX * 2;
		}
		return false;
	}
	
	void GestureLayer::longTouchHandler() {
		if (_enableLongTouch && _tapOk && _touchHistories.size() == 1) {
			const TouchHistory& th = _touchHistories[0];
			if (fgLongTouch(th.start) == GestureResult::OK) {
				_tapOk = false;
			}
		}
	}
	
	void GestureLayer::waitForDoubleTapHandler() {
		if (_enableDoubleTap) {
			fgTap(_prevTap);
		}
	}
}
