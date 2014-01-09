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
 
}
