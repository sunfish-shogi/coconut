//
//  HttpUtils.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/21.
//
//

#ifndef __coconut__HttpUtils__
#define __coconut__HttpUtils__

#include <vector>
#include <string>

namespace coconut {
	
	class HttpUtils {
	private:
		
		HttpUtils() {}
		
	public:
		
		static std::string getHeaderParam(const std::vector<std::string>& headers, const char* key);
		
	};
	
}


#endif /* defined(__coconut__HttpUtils__) */
