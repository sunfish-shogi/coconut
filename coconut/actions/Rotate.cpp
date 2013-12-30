//
//  Rotate.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#include "Rotate.h"

USING_NS_CC;

namespace coconut {
	
	Rotate* Rotate::create(float duration, float rps)
	{
    Rotate *pRet = new Rotate();
    pRet->initWithDuration(duration, rps);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool Rotate::initWithDuration(float duration, float rps)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_rps = rps;
			return true;
    }
		
    return false;
	}
	
	Rotate* Rotate::clone(void) const
	{
		// no copy constructor
		auto a = new Rotate();
    a->initWithDuration(_duration, _rps);
		a->autorelease();
		return a;
	}
	
	void Rotate::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
    _previousRotation = _startRotation = target->getRotation();
	}
	
	Rotate* Rotate::reverse() const
	{
    return Rotate::create(_duration, -_rps);
	}
	
	void Rotate::update(float t)
	{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
			float currentRotation = _target->getRotation();
			float diff = currentRotation - _previousRotation;
			_startRotation = _startRotation + diff;
			float newRotation =  _startRotation + _rps * _duration * t;
			_target->setRotation(newRotation);
			_previousRotation = newRotation;
#else
			float newRotation =  _startRotation + _rps * _duration * t;
			_target->setRotation(newRotation);
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
	}
	
}

