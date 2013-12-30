//
//  StringUtils.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/22.
//
//

#include "StringUtils.h"
#include <sstream>

namespace coconut {
  
	std::string StringUtils::binary2Hex(const char* data, unsigned size,
																			const std::string& prefix, const std::string& separator) {
		std::ostringstream oss;
		oss << prefix;
		oss << std::hex;
		for (unsigned i = 0; i < size; i++) {
			if (i != 0) {
				oss << separator;
			}
			oss << ((unsigned char)data[i] / 0x10U);
			oss << ((unsigned char)data[i] % 0x10U);
		}
		return oss.str();
	}

}
