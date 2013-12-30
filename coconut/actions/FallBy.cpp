//
//  FallBy.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#include "FallBy.h"

USING_NS_CC;

namespace coconut {
	
	FallBy* FallBy::create(float duration, const Point& initialVelocity, float gravity)
	{
    FallBy *pRet = new FallBy();
    pRet->initWithDuration(duration, initialVelocity, gravity);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool FallBy::initWithDuration(float duration, const Point& initialVelocity, float gravity)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_initialVelocity = initialVelocity;
			_gravity = gravity;
			return true;
    }
		
    return false;
	}
	
	FallBy* FallBy::clone(void) const
	{
		// no copy constructor
		auto a = new FallBy();
    a->initWithDuration(_duration, _initialVelocity, _gravity);
		a->autorelease();
		return a;
	}
	
	void FallBy::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition();
	}
	
	FallBy* FallBy::reverse() const
	{
		CCASSERT(false, "");
		float a = - _gravity / 2.0;
		float b = _initialVelocity.y / _gravity;
    return FallBy::create(_duration,
													Point(-_initialVelocity.x, 2.0 * a * (_duration - b)),
													_gravity);
	}
	
	void FallBy::update(float t)
	{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
			Point currentPos = _target->getPosition();
			Point diff = currentPos - _previousPosition;
			_startPosition = _startPosition + diff;
			Point newPos =  _startPosition + position(t);
			_target->setPosition(newPos);
			_previousPosition = newPos;
#else
			_target->setPosition(ccpAdd( _startPosition, position(t)));
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
	}
	
	Point FallBy::position(float t) const {
		float a = - _gravity / 2.0;
		float b = _initialVelocity.y / _gravity;
		float d = _duration * t - b;
		return Point(_initialVelocity.x * _duration * t,
								 a * (d * d - b * b));
	}
	
}

