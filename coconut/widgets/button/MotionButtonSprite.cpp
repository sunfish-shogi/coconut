//
//  MotionButtonSprite.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#include "MotionButtonSprite.h"

USING_NS_CC;

namespace coconut {
	
	bool MotionButtonSprite::init(Node* sprite, Action* touchAction, Action* detouchAction) {
		if (!ButtonSprite::init()) {
			return false;
		}
		
		CCASSERT(sprite != nullptr, "sprite must not be null.");
		CCASSERT(touchAction != nullptr, "sprite must not be null.");
		
		_sprite = sprite;
		_touchAction = touchAction;
		_detouchAction = detouchAction;
		
		_basePosition = _sprite->getPosition();
		_baseScale = _sprite->getScale();
		_baseRotationX = _sprite->getRotationX();
		_baseRotationY = _sprite->getRotationY();
		Sprite* s = dynamic_cast<Sprite*>(_sprite);
		_baseOpacity = s != nullptr ? s->getOpacity() : 255;
		
		addChild(_sprite);
		retainActions();
		
		reset();
		
		return true;
	}
	
	void MotionButtonSprite::retainActions() {
		if (_touchAction != nullptr) {
			_touchAction->retain();
		}
		if (_detouchAction != nullptr) {
			_detouchAction->retain();
		}
	}
	
	void MotionButtonSprite::releaseActions() {
		if (_touchAction != nullptr) {
			_touchAction->release();
		}
		if (_detouchAction != nullptr) {
			_detouchAction->release();
		}
	}
	
	bool MotionButtonSprite::isInside(Touch* touch) {
		Node* node = _sprite;
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
	
	void MotionButtonSprite::reset() {
		_sprite->setPosition(_basePosition);
		_sprite->setScale(_baseScale);
		_sprite->setRotationX(_baseRotationX);
		_sprite->setRotationY(_baseRotationY);
		Sprite* s = dynamic_cast<Sprite*>(_sprite);
		if (s != nullptr) {
			s->setOpacity(_baseOpacity);
		}
	}
	
	void MotionButtonSprite::touch() {
		if (_sprite != nullptr && _touchAction != nullptr) {
			_sprite->runAction(_touchAction);
		}
	}
	
	void MotionButtonSprite::detouch() {
		if (_sprite != nullptr && _detouchAction != nullptr) {
			_sprite->runAction(_detouchAction);
		}
	}
		
	MotionButtonSprite* MotionButtonSprite::create(Node* sprite, Action* touchAction, Action* detouchAction) {
		MotionButtonSprite* instance = new MotionButtonSprite();
		if (instance != nullptr && instance->init(sprite, touchAction, detouchAction)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}
