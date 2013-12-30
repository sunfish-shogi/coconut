//
//  MotionButtonSprite.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#ifndef __coconut__MotionButtonSprite__
#define __coconut__MotionButtonSprite__

#include "ButtonSprite.h"

namespace coconut {
	
	class MotionButtonSprite : public ButtonSprite {
	private:
		
		cocos2d::Node* _sprite;
		cocos2d::Action* _touchAction;
		cocos2d::Action* _detouchAction;
		
		cocos2d::Point _basePosition;
		float _baseScale;
		float _baseRotationX;
		float _baseRotationY;
		GLubyte _baseOpacity;
		
		void retainActions();
		void releaseActions();
		
	protected:
		
	public:
		
		CC_DEPRECATED_ATTRIBUTE
		MotionButtonSprite() : _sprite(nullptr), _touchAction(nullptr), _detouchAction(nullptr) {}
		virtual ~MotionButtonSprite() {
			releaseActions();
		}
		
		bool init(cocos2d::Node* sprite, cocos2d::Action* touchAction, cocos2d::Action* detouchAction);
		
		virtual bool isInside(cocos2d::Touch* touch) override;
		virtual void reset() override;
		virtual void touch() override;
		virtual void detouch() override;
		
		CC_DEPRECATED_ATTRIBUTE
		static MotionButtonSprite* create(cocos2d::Node* sprite, cocos2d::Action* touchAction, cocos2d::Action* detouchAction);
		
	};
	
}

#endif /* defined(__coconut__MotionButtonSprite__) */
