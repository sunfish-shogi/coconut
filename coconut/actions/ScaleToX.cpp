//
//  ScaleToX.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/29.
//
//

#include "ScaleToX.h"

USING_NS_CC;

namespace coconut {
	
	ScaleToX* ScaleToX::create(float duration, float scale)
	{
    ScaleToX *pRet = new ScaleToX();
    pRet->initWithDuration(duration, scale);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool ScaleToX::initWithDuration(float duration, float scale)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_scale = scale;
			return true;
    }
		
    return false;
	}
	
	ScaleToX* ScaleToX::clone(void) const
	{
		// no copy constructor
		auto a = new ScaleToX();
    a->initWithDuration(_duration, _scale);
		a->autorelease();
		return a;
	}
	
	void ScaleToX::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
		_previous = _start = target->getScaleX();
	}
	
	ScaleToX* ScaleToX::reverse() const
	{
		CCASSERT(false, "reverse() not supported in ScaleToX");
		return nullptr;
	}
	
	void ScaleToX::update(float t)
	{
    if (_target)
    {
			_target->setScaleX(_start + (_scale - _start) * t);
    }
	}
	
}
