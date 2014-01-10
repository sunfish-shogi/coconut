//
//  ScheduleManager.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/02.
//
//

#include "ScheduleManager.h"

namespace coconut {
	
	ScheduleManager::ScheduleManager() {
	}
	
	ScheduleManager::~ScheduleManager() {
		clear();
	}
	
	void ScheduleManager::clear() {
		while (_schedules.size() > 0) {
			Schedule* schedule = _schedules.front();
			schedule->cancel();
			_schedules.pop_front();
		}
	}
	
	void ScheduleManager::pause() {
		for (auto ite = _schedules.begin(); ite != _schedules.end(); ite++) {
			(*ite)->pause();
		}
	}
	
	void ScheduleManager::resume() {
		for (auto ite = _schedules.begin(); ite != _schedules.end(); ite++) {
			(*ite)->resume();
		}
	}
		
	void ScheduleManager::release(Schedule* schedule) {
		if (schedule) {
			for (auto ite = _schedules.begin(); ite != _schedules.end(); ite++) {
				if (*ite == schedule) {
					_schedules.erase(ite);
					break;
				}
			}
		}
	}
	
	void ScheduleManager::cancel(const Schedule* schedule) {
		if (schedule) {
			for (auto ite = _schedules.begin(); ite != _schedules.end(); ite++) {
				if (*ite == schedule) {
					(*ite)->cancel();
					_schedules.erase(ite);
					break;
				}
			}
		}
	}
	
	const Schedule* ScheduleManager::schedule(int priority, const Schedule::Callback& callback) {
		Schedule* schedule = Schedule::create([=](float d) {
			callback(d);
		});
		_schedules.push_back(schedule);
		schedule->schedule(priority);
		return schedule;
	}
	
	const Schedule* ScheduleManager::scheduleOnce(float dt, const std::function<void()>& callback) {
		Schedule* schedule = Schedule::create([=](float d) {
			callback();
			release(schedule);
		});
		_schedules.push_back(schedule);
		schedule->scheduleOnce(dt);
		return schedule;	
	}
	
	const Schedule* ScheduleManager::scheduleForever(float interval, float dt, const std::function<void()>& callback) {
		Schedule* schedule = Schedule::create([=](float d) {
			callback();
		});
		_schedules.push_back(schedule);
		schedule->scheduleForever(interval, dt);
		return schedule;
	}
	
}
