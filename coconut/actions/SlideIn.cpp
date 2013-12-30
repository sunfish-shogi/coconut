//
//  SlideIn.cpp
//  patras
//
//  Created by Kubo Ryosuke on 2013/12/20.
//
//

#include "SlideIn.h"
#include "SlideOut.h"

USING_NS_CC;

namespace coconut {
	
	SlideIn* SlideIn::create(float duration, const Point& offset)
	{
    SlideIn *pRet = new SlideIn();
    pRet->initWithDuration(duration, offset);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool SlideIn::initWithDuration(float duration, const Point& offset)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_offset = offset;
			return true;
    }
		
    return false;
	}
	
	SlideIn* SlideIn::clone(void) const
	{
		// no copy constructor
		auto a = new SlideIn();
    a->initWithDuration(_duration, _offset);
		a->autorelease();
		return a;
	}
	
	void SlideIn::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition() + _offset;
		target->setVisible(true);
		target->setPosition(_startPosition);
	}
	
	ActionInterval* SlideIn::reverse() const
	{
		CCASSERT(false, "");
    return SlideOut::create(_duration, _offset);
	}
	
	void SlideIn::update(float t)
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
			_target->setPosition(_startPosition + position(t));
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
	}
	
	Point SlideIn::position(float t) const {
		return -_offset * t;
	}
	
}
