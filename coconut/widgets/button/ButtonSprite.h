//
//  ButtonSprite.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#ifndef __coconut__ButtonSprite__
#define __coconut__ButtonSprite__

#include "cocos2d.h"

namespace coconut {
	
	class ButtonSprite : public cocos2d::Node {
	public:
		
		virtual bool isInside(cocos2d::Touch* touch) = 0;
		virtual void reset() = 0;
		virtual void touch() = 0;
		virtual void detouch() = 0;
		
	};
	
}

#endif /* defined(__coconut__ButtonSprite__) */
