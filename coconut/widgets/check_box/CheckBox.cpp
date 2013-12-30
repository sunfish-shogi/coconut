//
//  CheckBox.cpp
//
//  Created by Kubo Ryosuke on 13/09/06.
//
//

#include "CheckBox.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define LABEL_MARGIN							10.0f
#define Z_ORDER_CHECK							103
#define Z_ORDER_BG								101
#define Z_ORDER_LABEL							102

namespace coconut {
	
	bool CheckGroup::init() {
		_value = 0;
		return true;
	}
	
	void CheckGroup::join(CheckBox* checkBox, int value) {
		CCASSERT(checkBox->_group == nullptr, "check box is already joined.");
		
		Member member;
		member.checkBox = checkBox;
		member.value = value;
		_members.push_back(member);
		
		checkBox->_group = this;
		checkBox->setValue(_value == value);
		checkBox->onChecked([=]() {
			_value = value;
			uncheck(checkBox);
			emitChanged();
		});
		
		retain();
	}
	
	void CheckGroup::uncheck(CheckBox* except) {
		for (auto ite = _members.begin(); ite != _members.end(); ite++) {
			if ((*ite).checkBox != except) {
				(*ite).checkBox->setValue(false);
			}
		}
	}
	
	void CheckGroup::setValue(int value) {
		_value = value;
		for (auto ite = _members.begin(); ite != _members.end(); ite++) {
			if ((*ite).value == value) {
				(*ite).checkBox->setValue(true);
			} else {
				(*ite).checkBox->setValue(false);
			}
		}
	}
	
	CheckBox::CheckBox() : _check(nullptr), _background(nullptr), _label(nullptr), _value(true), _group(nullptr) {
	}
	
	CheckBox::~CheckBox() {
		if (_group != nullptr) {
			_group->release();
		}
	}
	
	bool CheckBox::init(Node* check, Sprite* background, Node* label) {
		if (!Layer::init()) {
			return false;
		}
		
		_check = check;
		_background = background;
		_label = label;
		
		if (_background == nullptr) {
			_background = Sprite::create("coconut/checkbox_background.png");
		}
		_background->setPosition(Point(0, 0));
		addChild(_background, Z_ORDER_BG);
		
		if (_check == nullptr) {
			float fontSize = _background->getContentSize().height * 0.8;
			_check = LabelTTF::create("x", "Helvetica", fontSize);
		}
		_check->setPosition(Point(0, 0));
		addChild(_check, Z_ORDER_CHECK);
		
		CCASSERT(_label != nullptr, "label could not be null.");
		Size labelSize = _label->getContentSize();
		Size checkSize = _check->getContentSize();
		if (_background != nullptr) {
			checkSize = _background->getContentSize();
		}
		addChild(_label, Z_ORDER_LABEL);
		_label->setPosition(Point((checkSize.width + labelSize.width) / 2.0f + LABEL_MARGIN, 0.0f));
		
		updateStatus();
		
		setTouchEnabled(true);
		setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
		
		return true;
	}
	
	bool CheckBox::onTouchBegan(Touch* touch, Event* event) {
		Point pos = touch->getStartLocation();
		if (isEnablePosition(convertToNodeSpace(pos))) {
			return true;
		}
		return false;
	}
	
	void CheckBox::onTouchMoved(Touch* touch, Event* event) {
	}
	
	void CheckBox::onTouchEnded(Touch* touch, Event* event) {
		Point pos = touch->getLocation();
		if (isEnablePosition(convertToNodeSpace(pos))) {
			if (!_value || _group == nullptr) {
				setValue(!_value, true);
			}
		}
	}
	
	bool CheckBox::isEnablePosition(const Point& pos) {
		return isInside(_background, pos) || isInside(_label, pos);
	}
		
	bool CheckBox::isInside(Node* obj, const Point& pos) {
		const Point& center = obj->getPosition();
		const Size& size = obj->getContentSize();
		return pos.x >= center.x - size.width / 2.0
				&& pos.x <= center.x + size.width / 2.0
				&& pos.y >= center.y - size.height / 2.0
				&& pos.y <= center.y + size.height / 2.0;
	}
	
	void CheckBox::setValue(bool value, bool enableCallbacks) {
		if (value != _value) {
			_value = value;
			updateStatus();
			if (enableCallbacks) {
				if (value) {
					emitChecked();
				} else {
					emitUnchecked();
				}
				emitChanged();
			}
		}
	}
	
	void CheckBox::updateStatus() {
		_check->setVisible(_value);
	}
	
	CheckBox* CheckBox::create(Node* check, Sprite* background, Node* label) {
		CheckBox* checkBox = new CheckBox();
		if (checkBox != nullptr && checkBox->init(check, background, label)) {
			checkBox->autorelease();
			return checkBox;
		}
		CC_SAFE_DELETE(checkBox);
		return nullptr;
	}
		
	CheckBox* CheckBox::create(const char* label, const char* fontName, int fontSize) {
		CheckBox* checkBox = new CheckBox();
		if (checkBox != nullptr && checkBox->init(nullptr, nullptr, LabelTTF::create(label, fontName, fontSize))) {
			checkBox->autorelease();
			return checkBox;
		}
		CC_SAFE_DELETE(checkBox);
		return nullptr;
	}
	
}
