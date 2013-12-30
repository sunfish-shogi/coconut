//
//  Vibrate.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#include "Vibrate.h"

USING_NS_CC;

namespace coconut {
	
	Vibrate* Vibrate::create(float duration, float angle, float amplitude, float frequency)
	{
    Vibrate *pRet = new Vibrate();
    pRet->initWithDuration(duration, angle, amplitude, frequency);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool Vibrate::initWithDuration(float duration, float angle, float amplitude, float frequency)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_angle = angle;
			_amplitude = amplitude;
			_frequency = frequency;
			return true;
    }
		
    return false;
	}
	
	Vibrate* Vibrate::clone(void) const
	{
		// no copy constructor
		auto a = new Vibrate();
    a->initWithDuration(_duration, _angle, _amplitude, _frequency);
		a->autorelease();
		return a;
	}
	
	void Vibrate::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition();
	}
	
	Vibrate* Vibrate::reverse() const
	{
		CCASSERT(false, "");
    return Vibrate::create(_duration, _angle + 180.0, _amplitude, _frequency);
	}
	
	void Vibrate::update(float t)
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
			_target->setPosition( _startPosition + position(t));
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
	}
	
	Point Vibrate::position(float t) const {
		float d = sinf((1.0 - t) * M_PI_2) * _amplitude * sinf(t * _duration * _frequency * 2.0f * M_PI);
		return Point(cosf(_angle * M_PI / 180.0) * d,
								 sinf(_angle * M_PI / 180.0) * d);
	}
	
}

