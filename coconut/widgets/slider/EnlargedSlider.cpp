//
//  EnlargedSlider.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/12.
//
//

#include "EnlargedSlider.h"
#include "../../actions/PreferredSizeTo.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace coconut {
  
	bool EnlargedSlider::initWithSprite(cocos2d::extension::Scale9Sprite* bar,
																			float width,
																			cocos2d::Node* head,
																			cocos2d::Node* bg) {
		if (!Slider::init()) {
			return false;
		}
		
		_bar = bar;
		_width = width;
		_head = head;
		_bg = bg;
		
		
		if (_bar) {
			addChild(_bar);
		}
		if (_head) {
			addChild(_head);
		}
		if (_bg) {
			addChild(_bg);
		}
		
		refresh();
		
		return true;
	}
	
	Point EnlargedSlider::getBarPosition() const {
		return Point(_width*(rate()-1.0f)*0.5f, 0);
	}
	
	Size EnlargedSlider::getBarPreferredSize() const {
		return Size(_width*rate(), _bar->getOriginalSize().height);
	}
	
	Point EnlargedSlider::getHeadPosition() const {
		return Point(_width*(rate()-0.5f), 0);
	}
		
	void EnlargedSlider::refresh() {
		if (_bar) {
			_bar->setPreferredSize(getBarPreferredSize());
			_bar->setPosition(getBarPosition());
		}
		if (_head) {
			_head->setPosition(getHeadPosition());
		}
	}
	
	void EnlargedSlider::refreshWithScroll(float duration, const EaseBuilder& easeBuilder) {
		if (_bar) {
			_bar->stopAllActions();
			_bar->runAction(PreferredSizeTo::create(duration, getBarPreferredSize()));
			_bar->runAction(MoveTo::create(duration, getBarPosition()));
		}
		if (_head) {
			_head->stopAllActions();
			_head->runAction(MoveTo::create(duration, getHeadPosition()));
		}
	}
		
	EnlargedSlider* EnlargedSlider::createWithSpriteFrameName(const char* bar,
																														float left,
																														float right,
																														float width,
																														const char* head,
																														const char* bg) {
		EnlargedSlider* instance = new EnlargedSlider();
		Scale9Sprite* barSprite = Scale9Sprite::createWithSpriteFrameName(bar);
		Rect capInsets(left, 0, barSprite->getOriginalSize().width - (left+right), barSprite->getOriginalSize().height);
		barSprite->setCapInsets(capInsets);
		Sprite* headSprite = head ? Sprite::createWithSpriteFrameName(head) : nullptr;
		Sprite* bgSprite = bg ? Sprite::createWithSpriteFrameName(bg) : nullptr;
		if (instance != nullptr && instance->initWithSprite(barSprite, width, headSprite, bgSprite)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}
