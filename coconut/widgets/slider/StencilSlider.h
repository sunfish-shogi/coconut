//
//  StencilSlider.h
//	coconut
//
//  Created by Kubo Ryosuke on 2013/09/25.
//
//

#ifndef __coconut__StencilSlider__
#define __coconut__StencilSlider__

#include "Slider.h"

namespace coconut {
	
	class StencilSlider : public Slider {
	private:
		
		cocos2d::Node* _bar;
		cocos2d::Node* _barStencil;
		float _barWidth;
		cocos2d::Node* _bg;
		cocos2d::Node* _head;
		cocos2d::Point _headBegin;
		cocos2d::Point _headEnd;
		cocos2d::ClippingNode* _clipper;
		cocos2d::DrawNode* _stencil;
		
		cocos2d::Point getBarPosition() const;
		cocos2d::Point getHeadPosition() const;
		
	protected:
		
		virtual void refresh() override;
		virtual void refreshWithScroll(float duration, const EaseBuilder& easeBuilder) override;
		
	public:
		
		cocos2d::Node* getBar() {
			return _bar;
		}
		cocos2d::Node* getBackground() {
			return _bg;
		}
		cocos2d::Node* getHead() {
			return _head;
		}
		
		virtual bool initWithSprite(cocos2d::Node* bar, cocos2d::Node* barStencil, float barWidth, cocos2d::Node* bg,
																cocos2d::Node* head, const cocos2d::Point& headBegin, const cocos2d::Point& headEnd);
		
		static StencilSlider* create(cocos2d::Node* bar, cocos2d::Node* barStencil, float barWidth) {
			return create(bar, barStencil, barWidth, nullptr);
		}
		static StencilSlider* create(cocos2d::Node* bar, cocos2d::Node* barStencil, float barWidth, cocos2d::Node* bg);
		static StencilSlider* create(cocos2d::Node* bar, cocos2d::Node* barStencil, float barWidth, cocos2d::Node* bg,
													cocos2d::Node* head, const cocos2d::Point& headBegin, const cocos2d::Point& headEnd);
		
	};
	
}

#endif /* defined(__coconut__StencilSlider__) */
