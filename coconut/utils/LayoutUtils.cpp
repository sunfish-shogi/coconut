//
//  LayoutUtils.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/04.
//
//

#include "LayoutUtils.h"

USING_NS_CC;

namespace coconut {
	
	namespace {
		
		void args2vector(va_list params, std::vector<Node*>& nodes) {
			while (true) {
				Node* node = va_arg(params, Node*);
				if (node == nullptr) {
					break;
				}
				nodes.push_back(node);
			}
		}
		
	}
 
	Point LayoutUtils::visibleOrigin() {
		return Director::getInstance()->getVisibleOrigin();
	}
	
	Size LayoutUtils::visibleSize() {
		return Director::getInstance()->getVisibleSize();
	}
	
	Rect LayoutUtils::visibleRect() {
		const Size& winSize = Director::getInstance()->getVisibleSize();
		const Point& winOrigin = Director::getInstance()->getVisibleOrigin();
		return Rect(winOrigin.x, winOrigin.y, winSize.width, winSize.height);
	}
	
	Point LayoutUtils::visibleCenter() {
		const Rect& rect = visibleRect();
		return Point(rect.getMidX(), rect.getMidY());
	}
	
	Point LayoutUtils::visibleTopLeft() {
		const Rect& rect = visibleRect();
		return Point(rect.getMinX(), rect.getMaxY());
	}
	
	Point LayoutUtils::visibleTopRight() {
		const Rect& rect = visibleRect();
		return Point(rect.getMaxX(), rect.getMaxY());
	}
	
	Point LayoutUtils::visibleTopCenter() {
		const Rect& rect = visibleRect();
		return Point(rect.getMidX(), rect.getMaxY());
	}
	
	Point LayoutUtils::visibleMiddleLeft() {
		const Rect& rect = visibleRect();
		return Point(rect.getMinX(), rect.getMidY());
	}
	
	Point LayoutUtils::visibleMiddleRight() {
		const Rect& rect = visibleRect();
		return Point(rect.getMaxX(), rect.getMidY());
	}
	
	Point LayoutUtils::visibleMiddleCenter() {
		const Rect& rect = visibleRect();
		return Point(rect.getMidX(), rect.getMidY());
	}
	
	Point LayoutUtils::visibleBottomLeft() {
		const Rect& rect = visibleRect();
		return Point(rect.getMinX(), rect.getMinY());
	}
	
	Point LayoutUtils::visibleBottomRight() {
		const Rect& rect = visibleRect();
		return Point(rect.getMaxX(), rect.getMinY());
	}
	
	Point LayoutUtils::visibleBottomCenter() {
		const Rect& rect = visibleRect();
		return Point(rect.getMidX(), rect.getMinY());
	}
		
	void LayoutUtils::alignCenterH(const Point& center, float padding, Node* node0, ...) {
		va_list params;
		va_start(params, node0);
		std::vector<Node*> nodes;
		nodes.push_back(node0);
		args2vector(params, nodes);
		float widthSum = -padding;
		for (auto ite = nodes.begin(); ite != nodes.end(); ite++) {
			float width = (*ite)->getContentSize().width * (*ite)->getScale();
			widthSum += width + padding;
		}
		float x = center.x - widthSum * 0.5f;
		for (auto ite = nodes.begin(); ite != nodes.end(); ite++) {
			float width = (*ite)->getContentSize().width * (*ite)->getScale();
			(*ite)->setPosition(Point(x + width * 0.5f, center.y));
			x += width + padding;
		}
		va_end(params);
	}
 
}
