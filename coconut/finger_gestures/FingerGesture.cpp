//
//  FingerGesture.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/09.
//
//

#include "FingerGesture.h"
#include "../utils/TimeUtils.h"

USING_NS_CC;


namespace coconut {
  
	FingerGesture::FingerGesture() {
	}
	
	FingerGesture::FingerGesture(cocos2d::Node* target, bool multi) {
		registerWithNode(target, multi);
	}
	
	FingerGesture::~FingerGesture() {
		unregister();
	}
	
	void FingerGesture::init() {
		_touchListener = nullptr;
		_longTouchSchedule = nullptr;
		_singleTapSchedule = nullptr;
		
		_tapAllowableError = 5.0f;
		
		_enableDoubleTap = false;
		_doubleTapTimeThreshold = 300L;
		
		_enableLongTouch = false;
		_longTouchTimeThreshold = 1000L;
		
		_longTapTimeThreshold = 1000L;
		
		_flickAreaType = AreaType::Ellipse;
		_flickXThreshold = 500.0f;
		_flickYThreshold = 500.0f;
		_flickLifeSpan = 200;
		
		_swipeAreaType = AreaType::Ellipse;
		_swipeXThreshold = 30.0f;
		_swipeYThreshold = 30.0f;
		
		_largeVelocityTime = 0;
		_tapOk = false;
		_prevTapTime = 0;
		_swipeOk = false;
	}
	
	void FingerGesture::registerWithNode(cocos2d::Node* target, bool multi) {
		unregister();
		
    EventListener* listener = EventListenerTouchAllAtOnce::create();
    
		if (multi) {
			auto allAtOnce = EventListenerTouchAllAtOnce::create();
			allAtOnce->onTouchesBegan = CC_CALLBACK_2(FingerGesture::onTouchesBegan, this);
			allAtOnce->onTouchesMoved = CC_CALLBACK_2(FingerGesture::onTouchesMoved, this);
			allAtOnce->onTouchesEnded = CC_CALLBACK_2(FingerGesture::onTouchesEnded, this);
			allAtOnce->onTouchesCancelled = CC_CALLBACK_2(FingerGesture::onTouchesCancelled, this);
			listener = allAtOnce;
		} else {
			auto oneByOne = EventListenerTouchOneByOne::create();
			oneByOne->onTouchBegan = CC_CALLBACK_2(FingerGesture::onTouchBegan, this);
			oneByOne->onTouchMoved = CC_CALLBACK_2(FingerGesture::onTouchMoved, this);
			oneByOne->onTouchEnded = CC_CALLBACK_2(FingerGesture::onTouchEnded, this);
			oneByOne->onTouchCancelled = CC_CALLBACK_2(FingerGesture::onTouchCancelled, this);
			listener = oneByOne;
		}
    
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->addEventListenerWithSceneGraphPriority(listener, target);
		_target = target;
    _touchListener = listener;
	}
	
	void FingerGesture::unregister() {
		if (_touchListener) {
			auto dispatcher = Director::getInstance()->getEventDispatcher();
			dispatcher->removeEventListener(_touchListener);
			_touchListener = nullptr;
		}
	}
	
	Point FingerGesture::t2p(Touch* touch) {
		const Point& point = Director::getInstance()->convertToUI(touch->getLocationInView());
		return _target->convertToNodeSpace(point);
	}
	
	int FingerGesture::touchOpen(const std::vector<Touch*>& touches) {
		int count = 0;
		uint64_t currTime = TimeUtils::currentMillisec();
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
			if (fgTouchFilter && fgTouchFilter(point) == TouchFilterResult::Ok) {
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
	
	void FingerGesture::touchNext(const std::vector<Touch*>& touches) {
		uint64_t currTime = TimeUtils::currentMillisec();
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
	
	void FingerGesture::touchClose(const std::vector<Touch*>& touches, std::vector<TouchHistory>* ths) {
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
	
  bool FingerGesture::onTouchBegan(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		return touchesBegan(touches);
	}
	
  void FingerGesture::onTouchMoved(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		touchesMoved(touches);
	}
	
  void FingerGesture::onTouchEnded(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		touchesEnded(touches);
	}
	
	void FingerGesture::onTouchCancelled(Touch *touch, Event *event) {
		std::vector<Touch*> touches;
		touches.push_back(touch);
		touchesCancelled(touches);
	}
	
	void FingerGesture::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesBegan(touches);
	}
		
	void FingerGesture::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesMoved(touches);
	}
	
	void FingerGesture::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesEnded(touches);
	}
	
	void FingerGesture::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, Event* event) {
		touchesCancelled(touches);
	}
	
	bool FingerGesture::touchesBegan(const std::vector<Touch*>& touches) {
		int count = touchOpen(touches);
		
		// scheduler
		unscheduleLongTouch();
		unscheduleSingleTap();
		
		_tapOk = true;
		_swipeOk = true;

		if (_touchHistories.size() == 1) {
			// single touch
			const TouchHistory& th = _touchHistories[0];
			
			if (fgTouch && fgTouch(th.curr) == GestureResult::Ok) {
				_tapOk = false;
				return true;
			}
			
			scheduleLongTouch();
		}
		return count != 0;
	}
	
	void FingerGesture::touchesMoved(const std::vector<Touch*>& touches) {
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
			if (checkFlick() && fgFlick && fgFlick(th.start, _largeVelocity) == GestureResult::Ok) {
				_swipeOk = false;
				return;
			}
			
			// swipe
			if (checkSwipe(dsum) && fgSwipe && fgSwipe(th.start, dsum) == GestureResult::Ok) {
				_swipeOk = false;
				return;
			}
			
			// movement
			if (fgMove) { fgMove(th.curr); }
			if (fgMove) { fgMoveWithDelta(th.prev, delta); }
			
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
			if (fgMove) { fgMoveWithRotation(currMiddle, currRotation); }
			if (fgMove) { fgMoveWithDeltaRotation(prevMiddle, delta, deltaRotation); }
		}
	}
	
	void FingerGesture::touchesEnded(const std::vector<Touch*>& touches) {
		std::vector<TouchHistory> ths;
		touchClose(touches, &ths);
		
		// scheduler
		unscheduleLongTouch();
		unscheduleSingleTap();
		
		// single touch
		if (_touchHistories.size() == 0 && ths.size() == 1) {
			TouchHistory& th = ths[0];
			
			// double tap
			if (checkDoubleTap(th.startTime) && fgDoubleTap && fgDoubleTap(th.start) == GestureResult::Ok) {
				unscheduleSingleTap();
				_prevTapTime = 0;
				return;
			}
			
			// long tap
			if (checkLongTap(th.startTime)) {
				_prevTapTime = th.startTime;
				if (fgLongTap && fgLongTap(th.start) == GestureResult::Ok) {
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
					if (fgTap && fgTap(th.start) == GestureResult::Ok) {
						return;
					}
				}
			}
			
			// flick
			if (checkFlick() && fgFlickWithDetouch && fgFlickWithDetouch(th.start, _largeVelocity) == GestureResult::Ok) {
				return;
			}
			
			// swipe
			Point dsum = th.curr - th.start;
			if (checkSwipe(dsum) && fgSwipeWithDetouch && fgSwipeWithDetouch(th.start, dsum) == GestureResult::Ok) {
				return;
			}
			
			if (fgDetouch) { fgDetouch(th.curr); }
		}
	}
	
	void FingerGesture::touchesCancelled(const std::vector<Touch*>& touches) {
		touchClose(touches);
	}
		
	void FingerGesture::updateLargeVelocity(const Point& delta, long deltaTime) {
		Point velocity = Point(delta.x * 1000.0f / deltaTime,
													 delta.y * 1000.0f / deltaTime);
		if (isOutsidOfArea(velocity, _flickAreaType, _flickXThreshold, _flickYThreshold)) {
			_largeVelocity = velocity;
			_largeVelocityTime = TimeUtils::currentMillisec();
		} else if (delta.dot(_largeVelocity) < 0.0f) {
			_largeVelocityTime = 0;
		}
	}
	
	void FingerGesture::updateTap(const Point& dsum) {
		if (_tapOk && dsum.getLength() >= _tapAllowableError) {
			_tapOk = false;
			unscheduleLongTouch();
			unscheduleSingleTap();
		}
	}
		
	bool FingerGesture::checkDoubleTap(uint64_t startTime) {
		return _enableDoubleTap && _tapOk &&
				startTime - _prevTapTime <= _doubleTapTimeThreshold;
	}
		
	bool FingerGesture::checkLongTap(uint64_t startTime) {
		return _tapOk && (TimeUtils::currentMillisec() - startTime >= _longTapTimeThreshold);
	}
		
	bool FingerGesture::checkTap() {
		return _tapOk;
	}
		
	bool FingerGesture::checkFlick() {
		if (_swipeOk && _largeVelocityTime != 0) {
			if (_flickLifeSpan == 0) {
				return true;
			}
			uint64_t age = TimeUtils::currentMillisec() - _largeVelocityTime;
			if (age < _flickLifeSpan) {
				return true;
			}
		}
		return false;
	}
	
	bool FingerGesture::checkSwipe(const Point& d) {
		return _swipeOk && isOutsidOfArea(d, _swipeAreaType, _swipeXThreshold, _swipeYThreshold);
	}
	
	bool FingerGesture::isOutsidOfArea(const Point& v, AreaType areaType, float areaX, float areaY) {
		if (areaType == AreaType::Rectangle) {
			return fabsf(v.x) >= areaX || fabsf(v.y) >= areaY;
		} else if (areaType == AreaType::Ellipse) {
			return Point(v.x, v.y * areaX / areaY).getLengthSq() >= areaX * areaX * 2;
		}
		return false;
	}
	
	void FingerGesture::unscheduleLongTouch() {
		_scheduleManager.cancel(_longTouchSchedule);
		_longTouchSchedule = nullptr;
	}
	
	void FingerGesture::scheduleLongTouch() {
		if (_enableLongTouch) {
			unscheduleLongTouch();
			_longTouchSchedule = _scheduleManager.scheduleOnce(_longTouchTimeThreshold / 1000.0f, [this]() {
				longTouchHandler();
			});
		}
	}
	
	void FingerGesture::longTouchHandler() {
		if (_enableLongTouch && _tapOk && _touchHistories.size() == 1) {
			const TouchHistory& th = _touchHistories[0];
			if (fgLongTouch && fgLongTouch(th.start) == GestureResult::Ok) {
				_tapOk = false;
			}
		}
	}
	
	void FingerGesture::unscheduleSingleTap() {
		_scheduleManager.cancel(_singleTapSchedule);
		_singleTapSchedule = nullptr;
	}
	
	void FingerGesture::scheduleSingleTap() {
		if (_enableDoubleTap) {
			unscheduleSingleTap();
			_singleTapSchedule = _scheduleManager.scheduleOnce(_doubleTapTimeThreshold / 1000.0f, [this]() {
				doubleTapHandler();
			});
		}
	}
	
	void FingerGesture::doubleTapHandler() {
		if (_enableDoubleTap) {
			if (fgTap) { fgTap(_prevTap); }
		}
	}
		
}
