//
//  StringUtils.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/22.
//
//

#ifndef __coconut__StringUtils__
#define __coconut__StringUtils__

#include <string>
#include <vector>

namespace coconut {
  
	class StringUtils {
	private:
		
		StringUtils();
		
	public:
		
		static std::string binary2Hex(const char* data, unsigned size,
																	const std::string& prefix = "", const std::string& separator = "");
	};
}

#endif /* defined(__coconut__StringUtils__) */
