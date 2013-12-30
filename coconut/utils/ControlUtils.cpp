//
//  ControlUtils.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/19.
//
//

#include "ControlUtils.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace coconut {
	
	class ControlSwitchEx : public cocos2d::extension::ControlSwitch {
	private:
		std::function<void(bool)> _callback;
		void onChangeValue(Object* sender, Control::EventType controlEvent) {
			_callback(isOn());
		}
	public:
		void setCallback(const std::function<void(bool)>& callback) {
			_callback = callback;
		}
    static ControlSwitchEx* create(cocos2d::Sprite *maskSprite, cocos2d::Sprite * onSprite, cocos2d::Sprite * offSprite, cocos2d::Sprite * thumbSprite, LabelTTF* onLabel, LabelTTF* offLabel) {
			ControlSwitchEx* instance = new ControlSwitchEx();
			if (instance && instance->initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel)) {
				instance->autorelease();
				instance->addTargetWithActionForControlEvents(instance, cccontrol_selector(ControlSwitchEx::onChangeValue), Control::EventType::VALUE_CHANGED);
				return instance;
			}
			CC_SAFE_DELETE(instance);
			return nullptr;
		}
	};
	
	class ControlSliderEx : public cocos2d::extension::ControlSlider {
	private:
		std::function<void(float)> _callback;
		void onChangeValue(Object* sender, Control::EventType controlEvent) {
			_callback(getValue());
		}
	public:
		void setCallback(const std::function<void(float)>& callback) {
			_callback = callback;
		}
    static ControlSliderEx* create(Sprite * backgroundSprite,
																	 Sprite* progressSprite,
																	 Sprite* thumbSprite) {              
			ControlSliderEx* instance = new ControlSliderEx();
			if (instance && instance->initWithSprites(backgroundSprite, progressSprite, thumbSprite)) {
				instance->autorelease();
				instance->addTargetWithActionForControlEvents(instance, cccontrol_selector(ControlSliderEx::onChangeValue), Control::EventType::VALUE_CHANGED);
				return instance;
			}
			CC_SAFE_DELETE(instance);
			return nullptr;
		}
	};
	
	ControlSwitch* ControlUtils::createControlSwitch(Sprite *maskSprite,
																									 Sprite * onSprite,
																									 Sprite * offSprite,
																									 Sprite * thumbSprite,
																									 LabelTTF* onLabel,
																									 LabelTTF* offLabel,
																									 const std::function<void(bool)>& callback) {
		ControlSwitchEx* sw = ControlSwitchEx::create(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
		sw->setCallback(callback);
		return sw;
	}
	
	ControlSlider* ControlUtils::createControlSlider(const char* bgFile,
																									 const char* progressFile,
																									 const char* thumbFile,
																									 const std::function<void(float)>& callback) {
    Sprite *backgroundSprite = Sprite::create(bgFile);
    Sprite *progressSprite = Sprite::create(progressFile);
    Sprite *thumbSprite = Sprite::create(thumbFile);
    return createControlSlider(backgroundSprite, progressSprite, thumbSprite, callback);
	}
	
	ControlSlider* ControlUtils::createControlSlider(Sprite * backgroundSprite,
																									 Sprite* progressSprite,
																									 Sprite* thumbSprite,
																									 const std::function<void(float)>& callback) {
		ControlSliderEx* cs = ControlSliderEx::create(backgroundSprite, progressSprite, thumbSprite);
		cs->setCallback(callback);
		return cs;
	}
	
}
