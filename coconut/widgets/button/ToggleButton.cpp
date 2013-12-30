//
//  ToggleButton.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#include "ToggleButton.h"
#include "SimpleButtonSprite.h"

USING_NS_CC;

namespace coconut {
		
	bool ToggleButton::init() {
		if (!BaseButton::init()) {
			return false;
		}
		
		_current = 0;
		
		return true;
	}
		
	bool ToggleButton::init(const std::vector<ButtonSprite*> sprites)  {
		if (!init()) {
			return false;
		}
		
		addItem(sprites);
		
		return true;
	}
	
	bool ToggleButton::init(ButtonSprite* sprite, va_list params)  {
		if (!init()) {
			return false;
		}
		
		addItem(sprite, params);
		return true;
	}
	
	void ToggleButton::addOneItem(ButtonSprite* sprite) {
		int index = _sprites.size();
		_sprites.push_back(sprite);
		addChild(sprite);
		if (_current != index) {
			sprite->setVisible(false);
		}
	}
	
	void ToggleButton::addItem(const std::vector<ButtonSprite*> sprites) {
		for (auto ite = sprites.begin(); ite != sprites.end(); ite++) {
			addOneItem(*ite);
		}
	}
	
	void ToggleButton::addItem(ButtonSprite* sprite, ...) {
		va_list params;
		va_start(params, sprite);
		addItem(sprite, params);
		va_end(params);
	}
	
	void ToggleButton::addItem(ButtonSprite* sprite, va_list params) {
		addOneItem(sprite);
		while (true) {
			ButtonSprite* p = va_arg(params, ButtonSprite*);
			if (p == nullptr) {
				break;
			}
			addOneItem(p);
		}
	}
	
	void ToggleButton::addItemWithSprite(Node* sprite, Node* touchingSprite) {
		addOneItem(SimpleButtonSprite::create(sprite, touchingSprite));
	}
	
	void ToggleButton::addItemWithSpriteFileName(const char* sprite, const char* touchingSprite) {
		addOneItem(SimpleButtonSprite::createWithSpriteFileName(sprite, touchingSprite));
	}
	
	void ToggleButton::addItemWithSpriteFrameName(const char* sprite, const char* touchingSprite) {
		addOneItem(SimpleButtonSprite::createWithSpriteFrameName(sprite, touchingSprite));
	}
	
	void ToggleButton::addItemWithSpriteFrame(SpriteFrame* sprite, SpriteFrame* touchingSprite) {
		addOneItem(SimpleButtonSprite::createWithSpriteFrame(sprite, touchingSprite));
	}
	
	ButtonSprite* ToggleButton::targetNode() {
		return _sprites[_current];
	}
		
	void ToggleButton::btDetouchedInside() {
		if (_sprites.size() >= 2) {
			setCurrentIndex((_current + 1) % _sprites.size(), true);
		} else {
			log("toggle button has no replacable items.");
		}
	}
		
	void ToggleButton::setCurrentIndex(int index, bool enableCallback) {
		CCASSERT(index >= 0 && index < _sprites.size(), "invalid index.");
		_sprites[_current]->setVisible(false);
		_current = index;
		_sprites[_current]->setVisible(true);
		_sprites[_current]->reset();
		if (enableCallback) {
			emitChanged();
		}
	}
	
	ToggleButton* ToggleButton::create() {
		ToggleButton* instance = new ToggleButton();
		if (instance != nullptr && instance->init()) {
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	ToggleButton* ToggleButton::create(const std::vector<ButtonSprite*> sprites) {
		ToggleButton* instance = new ToggleButton();
		if (instance != nullptr && instance->init(sprites)) {
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	ToggleButton* ToggleButton::create(ButtonSprite* sprite, ...) {
		ToggleButton* instance = new ToggleButton();
		va_list params;
		va_start(params, sprite);
		if (instance != nullptr && instance->init(sprite, params)) {
			va_end(params);
			return instance;
		}
		va_end(params);
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}
