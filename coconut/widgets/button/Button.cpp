//
//  Button.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#include "Button.h"
#include "SimpleButtonSprite.h"

USING_NS_CC;

namespace coconut {
	
	bool Button::init(ButtonSprite* sprite) {
		if (!BaseButton::init()) {
			return false;
		}
		
		CCASSERT(sprite != nullptr, "sprite must not be null.");
		_sprite = sprite;
		addChild(_sprite);
		
		return true;
	}
	
	Button* Button::create(ButtonSprite* sprite) {
		Button* instance = new Button();
		if (instance != nullptr && instance->init(sprite)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	Button* Button::create(ButtonSprite* sprite, const std::function<void()>& callback) {
		Button* instance = create(sprite);
		instance->onPushed(callback);
		return instance;
	}
	
	Button* Button::createWithSprite(Node* sprite,
																	 Node* touchingSprite) {
		SimpleButtonSprite* buttonSprite = SimpleButtonSprite::create(sprite, touchingSprite);
		return create(buttonSprite);
	}
	
	Button* Button::createWithSpriteFileName(const char* sprite,
																					 const char* touchingSprite) {
		SimpleButtonSprite* buttonSprite = SimpleButtonSprite::createWithSpriteFileName(sprite, touchingSprite);
		return create(buttonSprite);
	}
	
	Button* Button::createWithSpriteFrameName(const char* sprite,
																						const char* touchingSprite) {
		SimpleButtonSprite* buttonSprite = SimpleButtonSprite::createWithSpriteFrameName(sprite, touchingSprite);
		return create(buttonSprite);
	}
	
	Button* Button::createWithSpriteFrame(SpriteFrame* sprite,
																				SpriteFrame* touchingSprite) {
		SimpleButtonSprite* buttonSprite = SimpleButtonSprite::createWithSpriteFrame(sprite, touchingSprite);
		return create(buttonSprite);
	}
	
	Button* Button::createWithSprite(Node* sprite,
																	 Node* touchingSprite,
																	 const std::function<void()>& callback) {
		Button* instance = createWithSprite(sprite, touchingSprite);
		instance->onPushed(callback);
		return instance;
	}
	
	Button* Button::createWithSpriteFileName(const char* sprite,
																					 const char* touchingSprite,
																					 const std::function<void()>& callback) {
		Button* instance = createWithSpriteFileName(sprite, touchingSprite);
		instance->onPushed(callback);
		return instance;
	}
	
	Button* Button::createWithSpriteFrameName(const char* sprite,
																						const char* touchingSprite,
																						const std::function<void()>& callback) {
		Button* instance = createWithSpriteFrameName(sprite, touchingSprite);
		instance->onPushed(callback);
		return instance;
	}
	
	Button* Button::createWithSpriteFrame(cocos2d::SpriteFrame* sprite,
																				cocos2d::SpriteFrame* touchingSprite,
																				const std::function<void()>& callback) {
		Button* instance = createWithSpriteFrame(sprite, touchingSprite);
		instance->onPushed(callback);
		return instance;
	}
	
}
