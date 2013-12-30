//
//  GeomUtils.h
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#ifndef coconut_GeomUtils_h
#define coconut_GeomUtils_h

#include "cocos2d.h"

namespace coconut {
	
	class GeomUtils {
	private:
		
		GeomUtils() {}
		
	public:
		
		static cocos2d::Rect outside(const cocos2d::Rect& rect1, const cocos2d::Rect& rect2);
		static cocos2d::Rect outside(cocos2d::Node* node);
		static cocos2d::Size outsideSize(cocos2d::Node* node);
		static cocos2d::Size scaledSize(cocos2d::Node* node);
		
		static cocos2d::Point leftBottom(const cocos2d::Rect& rect) {
			return cocos2d::Point(rect.getMinX(), rect.getMinY());
		}
		static cocos2d::Point leftTop(const cocos2d::Rect& rect) {
			return cocos2d::Point(rect.getMinX(), rect.getMaxY());
		}
		static cocos2d::Point rightBottom(const cocos2d::Rect& rect) {
			return cocos2d::Point(rect.getMaxX(), rect.getMinY());
		}
		static cocos2d::Point rightTop(const cocos2d::Rect& rect) {
			return cocos2d::Point(rect.getMaxX(), rect.getMaxY());
		}
		
	};
	
}

#endif //coconut_GeomUtils_h
