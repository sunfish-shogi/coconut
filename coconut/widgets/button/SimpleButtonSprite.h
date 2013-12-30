//
//  SimpleButtonSprite.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#ifndef __coconut__SimpleButtonSprite__
#define __coconut__SimpleButtonSprite__

#include "ButtonSprite.h"

namespace coconut {
	
	class SimpleButtonSprite : public ButtonSprite {
	private:
		
		cocos2d::Node* _sprite;
		cocos2d::Node* _touchingSprite;
		
	protected:
		
	public:
		
		SimpleButtonSprite() : _sprite(nullptr), _touchingSprite(nullptr) {}
		virtual ~SimpleButtonSprite() {}
		
		virtual bool init(cocos2d::Node* sprite, cocos2d::Node* touchingSprite = nullptr);
		
		virtual bool isInside(cocos2d::Touch* touch) override;
		virtual void reset() override;
		virtual void touch() override;
		virtual void detouch() override;
		
		static SimpleButtonSprite* create(cocos2d::Node* sprite, cocos2d::Node* touchingSprite = nullptr);
		static SimpleButtonSprite* createWithSpriteFileName(const char* sprite, const char* touchingSprite = nullptr);
		static SimpleButtonSprite* createWithSpriteFrameName(const char* sprite, const char* touchingSprite = nullptr);
		static SimpleButtonSprite* createWithSpriteFrame(cocos2d::SpriteFrame* sprite, cocos2d::SpriteFrame* touchingSprite = nullptr);
		
	};
	
};

#endif /* defined(__coconut__SimpleButtonSprite__) */
