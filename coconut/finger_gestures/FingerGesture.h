//
//  FingerGesture.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/09.
//
//

#ifndef __coconut__FingerGesture__
#define __coconut__FingerGesture__

#include "cocos2d.h"
#include "../schedule/ScheduleManager.h"

namespace coconut {
 	
	enum class AreaType {
		Rectangle, Ellipse
	};
	
	enum class TouchFilterResult {
		Reject, Ok
	};
	
	enum class GestureResult {
		Uncaught, Ok
	};
 
	class FingerGesture {
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
	
		cocos2d::Node* _target;
		cocos2d::EventListener* _touchListener;
			
		// histories
		std::vector<TouchHistory> _touchHistories;
		cocos2d::Point _largeVelocity;
		uint64_t _largeVelocityTime;
		bool _tapOk;
		cocos2d::Point _prevTap;
		uint64_t _prevTapTime;
		bool _swipeOk;
		
		ScheduleManager _scheduleManager;
		const Schedule* _longTouchSchedule;
		const Schedule* _singleTapSchedule;
		
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
	
		void init();
		
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
		
		void unscheduleLongTouch();
		void scheduleLongTouch();
		void longTouchHandler();
		
		void unscheduleSingleTap();
		void scheduleSingleTap();
		void doubleTapHandler();
		
	  bool touchesBegan(const std::vector<cocos2d::Touch*>& touches);
    void touchesMoved(const std::vector<cocos2d::Touch*>& touches);
    void touchesEnded(const std::vector<cocos2d::Touch*>& touches);
    void touchesCancelled(const std::vector<cocos2d::Touch*>& touches);
		
	public:
		
		FingerGesture();
		FingerGesture(cocos2d::Node* target, bool multi = false, bool swallow = true);
		virtual ~FingerGesture();
		
		void registerWithNode(cocos2d::Node* target, bool multi = false, bool swallow = true);
		void unregister();
		
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
		
		// listeners
	  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
		
		// callbacks
		std::function<TouchFilterResult(const cocos2d::Point& position)> fgTouchFilter;
		std::function<GestureResult(const cocos2d::Point& position)> fgTouch;
		std::function<GestureResult(const cocos2d::Point& position)> fgLongTouch;
		std::function<GestureResult(const cocos2d::Point& start,
																const cocos2d::Point& velocity)> fgFlick;
		std::function<GestureResult(const cocos2d::Point& start,
																const cocos2d::Point& delta)> fgSwipe;
		std::function<GestureResult(const cocos2d::Point& center, float scale)> fgPinch;
		std::function<GestureResult(const cocos2d::Point& position)> fgMove;
		std::function<GestureResult(const cocos2d::Point& position,
																const cocos2d::Point& delta)> fgMoveWithDelta;
		std::function<GestureResult(const cocos2d::Point& position,
																float rotation)> fgMoveWithRotation;
		std::function<GestureResult(const cocos2d::Point& position,
																const cocos2d::Point& delta,
																float rotation)> fgMoveWithDeltaRotation;
		std::function<GestureResult(const cocos2d::Point& position)> fgDetouch;
		std::function<GestureResult(const cocos2d::Point& position)> fgDoubleTap;
		std::function<GestureResult(const cocos2d::Point& position)> fgTap;
		std::function<GestureResult(const cocos2d::Point& position)> fgLongTap;
		std::function<GestureResult(const cocos2d::Point& start,
																const cocos2d::Point& velocity)> fgFlickWithDetouch;
		std::function<GestureResult(const cocos2d::Point& start,
																const cocos2d::Point& delta)> fgSwipeWithDetouch;
	
	};
	
}

#endif /* defined(__coconut__FingerGesture__) */
