//
//  Schedule.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#ifndef __coconut__Schedule__
#define __coconut__Schedule__

#include "cocos2d.h"

namespace coconut {
	
	class Schedule : cocos2d::Object {
	public:
		
		typedef std::function<void(float)> Callback;
		
	private:
		
		Callback _callback;
		float _dt;
		void proc() {
			_callback(_dt);
		}
		
	public:
		
		Schedule();
		Schedule(const Callback& callback);
		virtual ~Schedule();
		void setCallback(const Callback callback) {
			_callback = callback;
		}
		
		virtual void update(float dt) override {
			_callback(dt);
		}
		
		void schedule(int priority);
		void scheduleOnce(float dt);
		void scheduleForever(float interval, float dt = 0.0f);
		void cancel();
	
		void pause();
		void resume();
		
		static Schedule* create(const Callback& callback);
		
	};

}

#endif /* defined(__coconut__Schedule__) */
