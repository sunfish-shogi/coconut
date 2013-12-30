//
//  GestureLayer.h
//
//  Created by Kubo Ryosuke on 13/09/03.
//
//

#ifndef __coconut_GestureLayer_H__
#define __coconut_GestureLayer_H__

#include "cocos2d.h"
#include "../EventEmitter.hpp"

namespace coconut {
	
	namespace _AreaType {
		enum Type { RECTANGLE, ELLIPSE };
	}
	typedef _AreaType::Type AreaType;
	
	namespace _GestureResult {
		enum Type { UNCAUGHT, OK };
	}
	typedef _GestureResult::Type GestureResult;
	
	class GestureLayer : public cocos2d::Layer {
		
	private:
		
		struct TouchHistory {
			int id;
			cocos2d::Point start;
			cocos2d::Point prev;
			cocos2d::Point curr;
			uint64_t startTime;
			uint64_t prevTime;
			uint64_t currTime;
		};
		
		// histories
		std::vector<TouchHistory> _touchHistories;
		cocos2d::Point _largeVelocity;
		uint64_t _largeVelocityTime;
		bool _tapOk;
		cocos2d::Point _prevTap;
		uint64_t _prevTapTime;
		bool _swipeOk;
		
		// settings
		float _tapAllowableError;
		
		bool _enableDoubleTap;
		long _doubleTapTimeThreshold;
	
		bool _enableLongTouch;
		long _longTouchTimeThreshold;
	
		long _longTapTimeThreshold;
	
		AreaType _flickAreaType;
		float _flickXThreshold;
		float _flickYThreshold;
		long _flickLifeSpan;
	
		AreaType _swipeAreaType;
		float _swipeXThreshold;
		float _swipeYThreshold;
	
		// geometry
		static float angleAsRadian(const cocos2d::Point& s,
															 const cocos2d::Point& e) {
			float dx = e.x - s.x, dy = e.y - s.y;
			return dx == 0.0f ? (dy >= 0.0f ? M_PI_2 : -M_PI_2) : atan2f(dy, dx);
		}
		
		cocos2d::Point t2p(cocos2d::Touch* touch);
		
		int touchOpen(const std::vector<cocos2d::Touch*>& touches);
		void touchNext(const std::vector<cocos2d::Touch*>& touches);
		void touchClose(const std::vector<cocos2d::Touch*>& touches, std::vector<TouchHistory>* ths = nullptr);
		
		void updateLargeVelocity(const cocos2d::Point& delta, long deltaTime);
		void updateTap(const cocos2d::Point& d);
		bool checkDoubleTap(uint64_t startTime);
		bool checkLongTap(uint64_t startTime);
		bool checkTap();
		bool checkFlick();
		bool checkSwipe(const cocos2d::Point& d);
		static bool isOutsidOfArea(const cocos2d::Point& v, AreaType areaType, float areaX, float areaY);
		
		void unscheduleLongTouch() {
			unschedule(cocos2d::SEL_SCHEDULE(&GestureLayer::longTouchHandler));
		}
		void scheduleLongTouch() {
			if (_enableLongTouch) {
				scheduleOnce(cocos2d::SEL_SCHEDULE(&GestureLayer::longTouchHandler), _longTouchTimeThreshold / 1000.0f);
			}
		}
		void longTouchHandler();
		
		void unscheduleSingleTap() {
			unschedule(cocos2d::SEL_SCHEDULE(&GestureLayer::waitForDoubleTapHandler));
		}
		void scheduleSingleTap() {
			if (_enableDoubleTap) {
				scheduleOnce(cocos2d::SEL_SCHEDULE(&GestureLayer::waitForDoubleTapHandler), _doubleTapTimeThreshold / 1000.0f);
			}
		}
		void waitForDoubleTapHandler();
		
	  bool touchesBegan(const std::vector<cocos2d::Touch*>& touches);
    void touchesMoved(const std::vector<cocos2d::Touch*>& touches);
    void touchesEnded(const std::vector<cocos2d::Touch*>& touches);
    void touchesCancelled(const std::vector<cocos2d::Touch*>& touches);
		
	public:
		
		virtual bool init() override;
		
		CC_DEPRECATED_ATTRIBUTE
		GestureLayer();
		~GestureLayer();
		
		int getTouchCount() const {
			return _touchHistories.size();
		}
		
		// settings
		void setTapAllowableError(float val) { _tapAllowableError = val; }
		float getTapAllowableError() { return _tapAllowableError; }
		
		void setEnableDoubleTap(bool val) { _enableDoubleTap = val; }
		bool getEnableDoubleTap() { return _enableDoubleTap; }
		void setDoubleTapTimeThreshold(long val) { _doubleTapTimeThreshold = val; }
		long getDoubleTapTimeThreshold() { return _doubleTapTimeThreshold; }
		
		void setEnableLongTouch(bool val) { _enableLongTouch = val; }
		bool getEnableLongTouch() { return _enableLongTouch; }
		void setLongTouchTimeThreshold(long val) { _longTouchTimeThreshold = val; }
		long getLongTouchTimeThreshold() { return _longTouchTimeThreshold; }
		
		void setLongTapTimeThreshold(long val) { _longTapTimeThreshold = val; }
		long getLongTapTimeThreshold() { return _longTapTimeThreshold; }
		
		void setFlickAreaType(AreaType val) { _flickAreaType = val; }
		AreaType getFlickAreaType() { return _flickAreaType; }
		void setFlickThreshold(float val) { _flickXThreshold = val; _flickYThreshold = val; }
		void setFlickXThreshold(float val) { _flickXThreshold = val; }
		float getFlickXThreshold() { return _flickXThreshold; }
		void setFlickYThreshold(float val) { _flickYThreshold = val; }
		float getFlickYThreshold() { return _flickYThreshold; }
		void setFlickLifeSpan(long val) { _flickLifeSpan = val; }
		long getFlickLifeSpan() { return _flickLifeSpan; }
		
		void setSwipeAreaType(AreaType val) { _swipeAreaType = val; }
		AreaType getSwipeAreaType() { return _swipeAreaType; }
		void setSwipeThreshold(float val) { _swipeXThreshold = val; _swipeYThreshold = val; }
		void setSwipeXThreshold(float val) { _swipeXThreshold = val; }
		float getSwipeXThreshold() { return _swipeXThreshold; }
		void setSwipeYThreshold(float val) { _swipeYThreshold = val; }
		float getSwipeYThreshold() { return _swipeYThreshold; }
		
		// override
	  virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) override;
		
		// callbacks
		virtual GestureResult fgTouchBegan(const cocos2d::Point& position) {
			return GestureResult::OK;
		}
		
		virtual GestureResult fgTouch(const cocos2d::Point& position) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgLongTouch(const cocos2d::Point& position) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgFlick(const cocos2d::Point& start,
												 const cocos2d::Point& velocity) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgSwipe(const cocos2d::Point& start,
												 const cocos2d::Point& delta) {
			return GestureResult::UNCAUGHT;
		}
		virtual void fgPinch(const cocos2d::Point& center, float scale) {}
		virtual void fgMove(const cocos2d::Point& position) {}
		virtual void fgMove(const cocos2d::Point& previous,
												const cocos2d::Point& delta) {}
		virtual void fgMove(const cocos2d::Point& position,
												float rotation) {}
		virtual void fgMove(const cocos2d::Point& previous,
												const cocos2d::Point& delta,
												float deltaRotation) {}
		virtual void fgDetouch(const cocos2d::Point& position) {}
		
		virtual GestureResult fgDoubleTap(const cocos2d::Point& position) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgTap(const cocos2d::Point& position) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgLongTap(const cocos2d::Point& position) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgFlickWithDetouch(const cocos2d::Point& start,
																		const cocos2d::Point& velocity) {
			return GestureResult::UNCAUGHT;
		}
		virtual GestureResult fgSwipeWithDetouch(const cocos2d::Point& start,
																		const cocos2d::Point& delta) {
			return GestureResult::UNCAUGHT;
		}
		
	};

}

#endif /* defined(__coconut_GestureLayer_H__) */
