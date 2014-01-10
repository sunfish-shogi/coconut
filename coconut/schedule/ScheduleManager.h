//
//  ScheduleManager.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/02.
//
//

#ifndef __coconut__ScheduleManager__
#define __coconut__ScheduleManager__

#include "Schedule.h"

namespace coconut {
	
	class ScheduleManager {
	private:
		
		std::list<Schedule*> _schedules;
		
		void release(Schedule* schedule);
		
	public:
		
		ScheduleManager();
		virtual ~ScheduleManager();
		
		void clear();
		void pause();
		void resume();
		
		const Schedule* schedule(int priority, const Schedule::Callback& callback);
		const Schedule* scheduleOnce(float dt, const std::function<void()>& callback);
		const Schedule* scheduleForever(float interval, float dt, const std::function<void()>& callback);
		const Schedule* scheduleForever(float interval, const std::function<void()>& callback) {
			return scheduleForever(interval, 0.0f, callback);
		}
		void cancel(const Schedule* schedule);
	};
	
}

#endif /* defined(__coconut__ScheduleManager__) */
