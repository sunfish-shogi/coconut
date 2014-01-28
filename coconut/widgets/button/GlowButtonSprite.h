//
//  GlowButtonSprite.h
//  coconut
//
//  Created by Kubo Ryosuke on 2014/01/27.
//
//

#ifndef __coconut__GlowButtonSprite__
#define __coconut__GlowButtonSprite__

#include "ButtonSprite.h"

namespace coconut {
	
	class GlowButtonSprite : public ButtonSprite {
	private:
		
		cocos2d::Node* _sprite;
		cocos2d::Node* _glow;
		
	protected:
		
	public:
		
		GlowButtonSprite() : _sprite(nullptr) {}
		virtual ~GlowButtonSprite() {}

		virtual bool init(cocos2d::Node* sprite, bool front = false,
											const cocos2d::Color3B& color = cocos2d::Color3B::WHITE,
											float glowStrength = 1.0f);
	
		virtual bool isInside(cocos2d::Touch* touch) override;
		virtual void reset() override;
		virtual void touch() override;
		virtual void detouch() override;
	
		static GlowButtonSprite* create(cocos2d::Node* sprite, bool front = false,
																		const cocos2d::Color3B& color = cocos2d::Color3B::WHITE,
																		float glowStrength = 1.0f);
		static GlowButtonSprite* createWithSpriteFileName(const char* sprite, bool front = false,
																											const cocos2d::Color3B& color = cocos2d::Color3B::WHITE,
																											float glowStrength = 1.0f);
		static GlowButtonSprite* createWithSpriteFrameName(const char* sprite, bool front = false,
																											 const cocos2d::Color3B& color = cocos2d::Color3B::WHITE,
																											 float glowStrength = 1.0f);
		static GlowButtonSprite* createWithSpriteFrame(cocos2d::SpriteFrame* sprite, bool front = false,
																									 const cocos2d::Color3B& color = cocos2d::Color3B::WHITE,
																									 float glowStrength = 1.0f);
		
	};
	
};

#endif /* defined(__coconut__GlowButtonSprite__) */
