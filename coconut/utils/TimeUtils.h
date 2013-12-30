//
//  TimeUtils.h
//  MahjongPuzzleBattle
//
//  Created by Kubo Ryosuke on 2013/09/13.
//
//

#ifndef coconut_TimeUtils_h
#define coconut_TimeUtils_h

#include "cocos2d.h"

namespace coconut {
	
	class TimeUtils {
	private:
		
		TimeUtils() {}
		
	public:
		
		static double currentSeconds() {
			struct timeval cur;
			gettimeofday(&cur, NULL);
			return (double)cur.tv_sec + (double)cur.tv_usec * 1.0e-6;
		}
			
		static uint64_t currentMillisec() {
			struct timeval cur;
			gettimeofday(&cur, NULL);
			return ((uint64_t)cur.tv_sec * 1000 + cur.tv_usec / 1000);
		}

	};
	
}

#endif //coconut_TimeUtils_h
