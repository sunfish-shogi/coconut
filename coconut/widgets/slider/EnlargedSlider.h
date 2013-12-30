//
//  EnlargedSlider.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/12.
//
//

#ifndef __coconut__EnlargedSlider__
#define __coconut__EnlargedSlider__

#include "Slider.h"
#include "cocos-ext.h"

namespace coconut {
  
	class EnlargedSlider : public Slider {
	private:
				
		float _width;
		cocos2d::extension::Scale9Sprite* _bar;
		cocos2d::Node* _bg;
		cocos2d::Node* _head;
		
		cocos2d::Point getBarPosition() const;
		cocos2d::Size getBarPreferredSize() const;
		cocos2d::Point getHeadPosition() const;
		
	protected:
		
		virtual void refresh() override;
		virtual void refreshWithScroll(float duration, const EaseBuilder& easeBuilder) override;
		
	public:
		
		cocos2d::Node* getBorder() {
			return _bar;
		}
		cocos2d::Node* getBackground() {
			return _bg;
		}
		cocos2d::Node* getHead() {
			return _head;
		}
		
		bool initWithSprite(cocos2d::extension::Scale9Sprite* bar,
												float width,
												cocos2d::Node* head,
												cocos2d::Node* bg);
		
		static EnlargedSlider* createWithSpriteFrameName(const char* bar,
																										 float left,
																										 float right,
																										 float width,
																										 const char* head,
																										 const char* bg);
		
	};
	
}

#endif /* defined(__coconut__EnlargedSlider__) */
