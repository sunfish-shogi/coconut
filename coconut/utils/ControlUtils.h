//
//  ControlUtils.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/19.
//
//

#ifndef coconut_ControlUtils_h
#define coconut_ControlUtils_h

#include "cocos2d.h"
#include "cocos-ext.h"

namespace coconut {
	
	class ControlUtils {
	private:
		
		ControlUtils();
		
	public:
		
		// ControlSwitch
		static cocos2d::extension::ControlSwitch* createControlSwitch(cocos2d::Sprite *maskSprite,
																																	cocos2d::Sprite * onSprite,
																																	cocos2d::Sprite * offSprite,
																																	cocos2d::Sprite * thumbSprite,
																																	cocos2d::LabelTTF* onLabel,
																																	cocos2d::LabelTTF* offLabel,
																																	const std::function<void(bool)>& callback);
		static cocos2d::extension::ControlSwitch* createControlSwitch(cocos2d::Sprite *maskSprite,
																																	cocos2d::Sprite * onSprite,
																																	cocos2d::Sprite * offSprite,
																																	cocos2d::Sprite * thumbSprite,
																																	const std::function<void(bool)>& callback) {
			return createControlSwitch(maskSprite, onSprite, offSprite, thumbSprite, nullptr, nullptr, callback);
		}
		
		// ControlSlider
		static cocos2d::extension::ControlSlider* createControlSlider(const char* bgFile,
																																	const char* progressFile,
																																	const char* thumbFile,
																																	const std::function<void(float)>& callback);
		static cocos2d::extension::ControlSlider* createControlSlider(cocos2d::Sprite * backgroundSprite,
																																	cocos2d::Sprite* progressSprite,
																																	cocos2d::Sprite* thumbSprite,
																																	const std::function<void(float)>& callback);
		
	};
	
}

#endif
