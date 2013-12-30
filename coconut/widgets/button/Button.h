//
//  Button.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#ifndef __coconut__Button__
#define __coconut__Button__

#include "BaseButton.h"

namespace coconut {
	
	class Button : public BaseButton {
		
		DEFINE_EVENT_EMITTER(Pushed);
		
	private:
		
		ButtonSprite* _sprite;
		
	protected:
		
		virtual ButtonSprite* targetNode() {
			return _sprite;
		}
		
		// overrides
		virtual void btDetouchedInside() override {
			emitPushed();
		};
		
	public:
		
		virtual bool init(ButtonSprite* sprite);
		
		static Button* createCustom(ButtonSprite* sprite);
		static Button* createWithSprite(cocos2d::Node* sprite,
																		cocos2d::Node* touchingSprite = nullptr);
		static Button* createWithSpriteFileName(const char* sprite,
																						const char* touchingSprite = nullptr);
		static Button* createWithSpriteFrameName(const char* sprite,
																						 const char* touchingSprite = nullptr);
		static Button* createWithSpriteFrame(cocos2d::SpriteFrame* sprite,
																				 cocos2d::SpriteFrame* touchingSprite = nullptr);
		static Button* createWithSprite(cocos2d::Sprite* sprite,
																		cocos2d::Sprite* touchingSprite,
																		const std::function<void()>& callback);
		static Button* createWithSprite(cocos2d::Sprite* sprite,
																		const std::function<void()>& callback) {
			return createWithSprite(sprite, nullptr, callback);
		}
		static Button* createWithSpriteFileName(const char* sprite,
																						const char* touchingSprite,
																						const std::function<void()>& callback);
		static Button* createWithSpriteFileName(const char* sprite,
																						const std::function<void()>& callback) {
			return createWithSpriteFileName(sprite, nullptr, callback);
		}
		static Button* createWithSpriteFrameName(const char* sprite,
																						 const char* touchingSprite,
																						 const std::function<void()>& callback);
		static Button* createWithSpriteFrameName(const char* sprite,
																						 const std::function<void()>& callback) {
			return createWithSpriteFrameName(sprite, nullptr, callback);
		}
		static Button* createWithSpriteFrame(cocos2d::SpriteFrame* sprite,
																				 cocos2d::SpriteFrame* touchingSprite,
																				 const std::function<void()>& callback);
		static Button* createWithSpriteFrame(cocos2d::SpriteFrame* sprite,
																				 const std::function<void()>& callback) {
			return createWithSpriteFrame(sprite, nullptr, callback);
		}
		
	};
	
}

#endif /* defined(__coconut__Button__) */
