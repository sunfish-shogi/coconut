//
//  BaseButton.cpp
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#include "BaseButton.h"

USING_NS_CC;

namespace coconut {
	
	BaseButton::BaseButton() : _enabled(true), _touching(false), _touchListener(nullptr) {
	}
	
	bool BaseButton::init() {
		if (!Node::init()) {
			return false;
		}
		
		if (_running) {
			registerWithTouchDispatcher();
		}
		
		return true;
	}
	
	bool BaseButton::targetIsTouched(Touch* touch) {
		return targetNode()->isInside(touch);
	}
	
	void BaseButton::registerWithTouchDispatcher() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
        
    listener->onTouchBegan = CC_CALLBACK_2(BaseButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BaseButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BaseButton::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(BaseButton::onTouchCancelled, this);
        
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListener = listener;
	}
	
	void BaseButton::unregisterWithTouchDispatcher() {
		auto dispatcher = getEventDispatcher();
	  dispatcher->removeEventListener(_touchListener);
    _touchListener = nullptr;
	}
	
	void BaseButton::onEnter() {
		registerWithTouchDispatcher();
		Node::onEnter();
	}

	void BaseButton::onExit() {
		unregisterWithTouchDispatcher();
    Node::onExit();
	}
	
  bool BaseButton::onTouchBegan(Touch *touch, Event *event) {
		if (_enabled && targetIsTouched(touch)) {
			if (!_touching) {
				_touching = true;
				targetNode()->touch();
			}
			btTouched(); // callback
			emitTouched(); // event
			return true;
		}
		return false;
	}
	
  void BaseButton::onTouchMoved(Touch *touch, Event *event) {
		if (_enabled) {
			if (targetIsTouched(touch)) {
				if (!_touching) {
					_touching = true;
					targetNode()->touch();
					btMovedInside(); // callback
					emitMovedIn(); // event
				}
			} else {
				if (_touching) {
					_touching = false;
					targetNode()->detouch();
					btMovedOutside(); // callback
					emitMovedOut(); // event
				}
			}
		}
	}
	
  void BaseButton::onTouchEnded(Touch *touch, Event *event) {
		if (_enabled) {
			if (_touching) {
				_touching = false;
				targetNode()->detouch();
			}
			if (targetIsTouched(touch)) {
				btDetouchedInside(); // callback
				emitDetouchInside(); // event
			} else {
				btDetouchedOutside(); // callback
				emitDetouchOutside(); // event
			}
		}
	}
	
  void BaseButton::onTouchCancelled(Touch *touch, Event *event) {
		if (_enabled) {
			if (_touching) {
				_touching = false;
				targetNode()->detouch();
			}
			btDetouchedOutside(); // callback
			emitDetouchOutside(); // event
		}
	}
	
}
