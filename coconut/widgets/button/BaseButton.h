//
//  BaseButton.h
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#ifndef __coconut__BaseButton__
#define __coconut__BaseButton__

#include "ButtonSprite.h"
#include "../../EventEmitter.hpp"

namespace coconut {
  
	class BaseButton : public cocos2d::Node {
		
		DEFINE_EVENT_EMITTER(Touched);
		DEFINE_EVENT_EMITTER(MovedIn);
		DEFINE_EVENT_EMITTER(MovedOut);
		DEFINE_EVENT_EMITTER(DetouchInside);
		DEFINE_EVENT_EMITTER(DetouchOutside);
		
	private:
		
		int _touchPriority;
		bool _touching;
		bool _enabled;
		cocos2d::EventListener* _touchListener;
		
		void registerWithTouchDispatcher();
		void unregisterWithTouchDispatcher();
		
		bool targetIsTouched(cocos2d::Touch* touch);
			
	  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
		
	protected:
		
		BaseButton();
		
		virtual ButtonSprite* targetNode() = 0;
		
		// callbacks
		virtual void btTouched() {};
		virtual void btMovedInside() {};
		virtual void btMovedOutside() {};
		virtual void btDetouchedInside() {};
		virtual void btDetouchedOutside() {};
		
	public:
		
		virtual bool init() override;
		
		virtual void onEnter() override;
		virtual void onExit() override;
		
		bool isTouching() const {
			return _touching;
		}
		bool isEnabled() const {
			return _enabled;
		}
		void setEnabled(bool enabled) {
			_enabled = enabled;
		}
		
	};
	
}

#endif /* defined(__coconut__Button__) */
