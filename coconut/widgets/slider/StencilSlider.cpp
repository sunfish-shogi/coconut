//
//  StencilSlider.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/09/25.
//
//

#include "StencilSlider.h"
#include "../../utils/ArrayUtils.h"

USING_NS_CC;

namespace coconut {
	
	bool StencilSlider::initWithSprite(Node* bar, Node* barStencil, float barWidth, Node* bg,
																		 Node* head, const Point& headBegin, const Point& headEnd) {
		if (!Node::init()) {
			return false;
		}
		
		CCASSERT(bar != nullptr, "bar must not be null.");
		_bar = bar;
		_barStencil = barStencil;
		_barWidth = barWidth;
		_bg = bg;
		_head = head;
		_headBegin = headBegin;
		_headEnd = headEnd;
		
		if (_bg != nullptr) {
			addChild(_bg);
		}
		
		_clipper = ClippingNode::create();
		_clipper->addChild(_bar);
		_clipper->setStencil(_barStencil);
		addChild(_clipper);
		
		if (_head != nullptr) {
			addChild(_head);
		}
		
		refresh();
		
		return true;
	}
	
	Point StencilSlider::getBarPosition() const {
		return Point((rate()-1.0f)*_barWidth,0);
	}
	
	Point StencilSlider::getHeadPosition() const {
		return _headBegin + (_headEnd - _headBegin) * rate();
	}
	
	void StencilSlider::refresh() {
		_bar->stopAllActions();
		_bar->setPosition(getBarPosition());
		if (_head != nullptr) {
			_head->setPosition(getHeadPosition());
		}
	}
	
	void StencilSlider::refreshWithScroll(float duration, const EaseBuilder& easeBuilder) {
		_bar->stopAllActions();
		_bar->runAction(easeBuilder.build(MoveTo::create(duration, getBarPosition())));
		if (_head != nullptr) {
			_head->stopAllActions();
			_head->runAction(easeBuilder.build(MoveTo::create(duration, getHeadPosition())));
		}
	}
	
	StencilSlider* StencilSlider::create(Node* bar, Node* barStencil, float barWidth, Node* bg) {
		StencilSlider* instance = new StencilSlider();
		if (instance != nullptr && instance->initWithSprite(bar, barStencil, barWidth, bg, nullptr, Point::ZERO, Point::ZERO)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	StencilSlider* StencilSlider::create(Node* bar, Node* barStencil, float barWidth, Node* bg,
																			 Node* head, const Point& headBegin, const Point& headEnd) {
		StencilSlider* instance = new StencilSlider();
		if (instance != nullptr && instance->initWithSprite(bar, barStencil, barWidth, bg, head, headBegin, headEnd)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}
