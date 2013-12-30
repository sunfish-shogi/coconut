//
//  PreferredSizeTo.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/12.
//
//

#include "PreferredSizeTo.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace coconut {
	
	PreferredSizeTo* PreferredSizeTo::create(float duration, const Size& size)
	{
    PreferredSizeTo *pRet = new PreferredSizeTo();
    pRet->initWithDuration(duration, size);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool PreferredSizeTo::initWithDuration(float duration, const Size& size)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_size = size;
			return true;
    }
		
    return false;
	}
	
	PreferredSizeTo* PreferredSizeTo::clone(void) const
	{
		// no copy constructor
		auto a = new PreferredSizeTo();
    a->initWithDuration(_duration, _size);
		a->autorelease();
		return a;
	}
	
	void PreferredSizeTo::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
		_previous = _start = ((Scale9Sprite*)target)->getPreferredSize();
	}
	
	PreferredSizeTo* PreferredSizeTo::reverse() const
	{
		CCASSERT(false, "reverse() not supported in PreferredSizeTo");
		return nullptr;
	}
	
	void PreferredSizeTo::update(float t)
	{
    if (_target)
    {
			((Scale9Sprite*)_target)->setPreferredSize(_start*(1.0f-t) + _size*t);
    }
	}
	
}
