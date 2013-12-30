//
//  SlideOut.cpp
//  patras
//
//  Created by Kubo Ryosuke on 2013/12/20.
//
//

#include "SlideOut.h"
#include "SlideIn.h"

USING_NS_CC;

namespace coconut {
	
	SlideOut* SlideOut::create(float duration, const Point& offset)
	{
    SlideOut *pRet = new SlideOut();
    pRet->initWithDuration(duration, offset);
    pRet->autorelease();
		
    return pRet;
	}
	
	bool SlideOut::initWithDuration(float duration, const Point& offset)
	{
    if (ActionInterval::initWithDuration(duration))
    {
			_offset = offset;
			return true;
    }
		
    return false;
	}
	
	SlideOut* SlideOut::clone(void) const
	{
		// no copy constructor
		auto a = new SlideOut();
    a->initWithDuration(_duration, _offset);
		a->autorelease();
		return a;
	}
	
	void SlideOut::startWithTarget(Node *target)
	{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition();
	}
	
	ActionInterval* SlideOut::reverse() const
	{
		CCASSERT(false, "");
    return SlideIn::create(_duration, _offset);
	}
	
	void SlideOut::update(float t)
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
	
	Point SlideOut::position(float t) const {
		return _offset * t;
	}
	
}
