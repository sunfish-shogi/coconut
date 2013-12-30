//
//  GeomUtils.cpp
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#include "GeomUtils.h"

USING_NS_CC;

namespace coconut {
	
	Rect GeomUtils::outside(const Rect& rect1, const Rect& rect2) {
		Point bottomLeft(MIN(rect1.getMinX(), rect2.getMinX()),
										 MIN(rect1.getMinY(), rect2.getMinY()));
		Point topRight(MAX(rect1.getMaxX(), rect2.getMaxX()),
									 MAX(rect1.getMaxY(), rect2.getMaxY()));
		return Rect(bottomLeft.x,
								bottomLeft.y,
								topRight.x - bottomLeft.x,
								topRight.y - bottomLeft.y);
	}
	
	Rect GeomUtils::outside(Node* node) {
		const Point& pos = node->getPosition();
		const Size& size = outsideSize(node);
		const Point& anchor = node->getAnchorPoint();
		return Rect(pos.x + size.width * (1.0f -anchor.x),
								pos.y + size.height * (1.0f - anchor.y),
								size.width,
								size.height);
	}
		
	Size GeomUtils::outsideSize(Node* node) {
		const Size& size = scaledSize(node);
		float r = node->getRotation() * M_PI / 180.0f;
		float c = fabsf(cosf(r));
		float s = fabsf(sinf(r));
		return Size(c * size.width + s * size.height,
								s * size.width + c * size.height);
	}
	
	Size GeomUtils::scaledSize(Node* node) {
		const Size& size = node->getContentSize();
		return Size(size.width*node->getScaleX(),
								size.height*node->getScaleY());
	}
	
}
