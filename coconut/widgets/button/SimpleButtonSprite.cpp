//
//  SimpleButtonSprite.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#include "SimpleButtonSprite.h"

USING_NS_CC;

#define CALL_IF_NOT_NULL(p, func)						((p) != nullptr ? (func((p))) : nullptr)

namespace coconut {
		
	bool SimpleButtonSprite::init(Node* sprite, Node* touchingSprite) {
		if (!ButtonSprite::init()) {
			return false;
		}
		
		CCASSERT(sprite != nullptr, "sprite must not be null.");
		
		_sprite = sprite;
		addChild(_sprite);
		
		if (touchingSprite != nullptr) {
			_touchingSprite = touchingSprite;
			addChild(_touchingSprite);
		} else {
			_touchingSprite = sprite;
		}
		
		reset();
		
		return true;
	}
	
	bool SimpleButtonSprite::isInside(Touch* touch) {
		Node* node = _sprite->isVisible() ? _sprite : _touchingSprite;
		if (node != nullptr) {
			const Point& pos = node->convertToNodeSpace(Director::getInstance()->convertToUI(touch->getLocationInView()));
			const Point& targetPos = node->getPosition();
			const Point& anc = node->getPosition();
			const Size& size = node->getContentSize();
			const Rect rect(targetPos.x - size.width * anc.x,
											targetPos.y - size.height * anc.y,
											size.width, size.height);
			return rect.containsPoint(pos);
		}
		return false;
	}
	
	void SimpleButtonSprite::reset() {
		detouch();
	}
		
	void SimpleButtonSprite::touch() {
		if (_sprite != nullptr) {
			_sprite->setVisible(false);
		}
		if (_touchingSprite != nullptr) {
			_touchingSprite->setVisible(true);
		}
	}
	
	void SimpleButtonSprite::detouch() {
		if (_touchingSprite != nullptr) {
			_touchingSprite->setVisible(false);
		}
		if (_sprite != nullptr) {
			_sprite->setVisible(true);
		}
	}
	
	SimpleButtonSprite* SimpleButtonSprite::create(Node* sprite, Node* touchingSprite) {
		SimpleButtonSprite* instance = new SimpleButtonSprite();
		if (instance != nullptr && instance->init(sprite, touchingSprite)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	SimpleButtonSprite* SimpleButtonSprite::createWithSpriteFileName(const char* sprite, const char* touchingSprite) {
		SimpleButtonSprite* instance = new SimpleButtonSprite();
		if (instance != nullptr && instance->init(Sprite::create(sprite),
																							CALL_IF_NOT_NULL(touchingSprite, Sprite::create))) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	SimpleButtonSprite* SimpleButtonSprite::createWithSpriteFrameName(const char* sprite, const char* touchingSprite) {
		SimpleButtonSprite* instance = new SimpleButtonSprite();
		if (instance != nullptr && instance->init(Sprite::createWithSpriteFrameName(sprite),
																							CALL_IF_NOT_NULL(touchingSprite, Sprite::createWithSpriteFrameName))) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	SimpleButtonSprite* SimpleButtonSprite::createWithSpriteFrame(SpriteFrame* sprite, SpriteFrame* touchingSprite) {
		SimpleButtonSprite* instance = new SimpleButtonSprite();
		if (instance != nullptr && instance->init(Sprite::createWithSpriteFrame(sprite),
																							CALL_IF_NOT_NULL(touchingSprite, Sprite::createWithSpriteFrame))) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
};
