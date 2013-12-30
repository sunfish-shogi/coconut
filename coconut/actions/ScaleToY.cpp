//
//  ScaleToY.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/29.
//
//

#include "ScaleToY.h"

USING_NS_CC;

namespace coconut {
	
	ScaleToY* ScaleToY::create(float duration, float scale)
	{
    ScaleToY *pRet = new ScaleToY();
    pRet->initWithDuration(duration, scale);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool ScaleToY::initWithDuration(float duration, float scale)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_scale = scale;
			return true;
    }
		
    return false;
	}
	
	ScaleToY* ScaleToY::clone(void) const
	{
		// no copy constructor
		auto a = new ScaleToY();
    a->initWithDuration(_duration, _scale);
		a->autorelease();
		return a;
	}
	
	void ScaleToY::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
		_previous = _start = target->getScaleY();
	}
	
	ScaleToY* ScaleToY::reverse() const
	{
		CCASSERT(false, "reverse() not supported in ScaleToY");
		return nullptr;
	}
	
	void ScaleToY::update(float t)
	{
    if (_target)
    {
			_target->setScaleY(_start + (_scale - _start) * t);
    }
	}
	
}
