//
//  ChangeZOrder.cpp
//  patras
//
//  Created by Kubo Ryosuke on 2014/01/28.
//
//

#include "ChangeZOrder.h"

namespace coconut {

	ChangeZOrder * ChangeZOrder::create(int zOrder) {
		ChangeZOrder *ret = new ChangeZOrder();
		
		if (ret && ret->init(zOrder)) {
			ret->autorelease();
		}
		
		return ret;
	}
	
	bool ChangeZOrder::init(int zOrder) {
		_zOrder = zOrder;
		return true;
	}
	
	void ChangeZOrder::update(float time) {
		CC_UNUSED_PARAM(time);
		_target->setZOrder(_zOrder);
	}
	
	ChangeZOrder *ChangeZOrder::reverse() const
	{
		return ChangeZOrder::create(_zOrder);
	}
	
	ChangeZOrder * ChangeZOrder::clone() const
	{
		auto a = new ChangeZOrder();
		a->init(_zOrder);
		a->autorelease();
		return a;
	}
	
}
