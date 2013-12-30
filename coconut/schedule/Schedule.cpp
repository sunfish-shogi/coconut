//
//  Schedule.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#include "Schedule.h"

USING_NS_CC;

namespace coconut {
	
	Schedule::Schedule() {
	}
	
	Schedule::Schedule(const Callback& callback) : _callback(callback) {
	}
	
	Schedule::~Schedule() {
		cancel();
	}
	
	void Schedule::schedule(int priority) {
		Director::getInstance()->getScheduler()->scheduleUpdateForTarget(this, priority, false);
	}
	
	void Schedule::scheduleOnce(float dt) {
		_dt = dt;
		Director::getInstance()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&Schedule::proc),
																															this, 0.0f, 0, dt, false);
	}
	
	void Schedule::scheduleForever(float interval, float dt) {
		_dt = dt;
		Director::getInstance()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&Schedule::proc),
																															this, interval, kRepeatForever, dt, false);
	}
	
	void Schedule::cancel() {
		Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
		Director::getInstance()->getScheduler()->unscheduleUpdateForTarget(this);
	}
	
	Schedule* Schedule::create(const Callback& callback) {
		Schedule* instance = new Schedule(callback);
		if (instance != nullptr) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}

