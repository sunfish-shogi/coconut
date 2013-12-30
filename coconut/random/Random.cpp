//
//  Random.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/05.
//
//

#include "Random.h"

namespace coconut {
	
#if USE_RANDOM_DEVICE
	std::random_device Random::rd;
	std::mt19937 Random::mt(rd);
#else
	std::mt19937 Random::mt(time(nullptr));
#endif
	
}
