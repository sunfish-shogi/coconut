//
//  HttpUtils.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/21.
//
//

#include "HttpUtils.h"

namespace coconut {
	
	std::string HttpUtils::getHeaderParam(const std::vector<std::string>& headers, const char* key) {
		for (auto ite = headers.begin(); ite != headers.end(); ite++) {
			std::string::size_type pos = (*ite).find_first_of(':');
			if (pos != std::string::npos && (*ite).substr(0, pos) == key) {
				pos = (*ite).find_first_not_of(' ', pos + 1);
				return (*ite).substr(pos);
			}
		}
		return "";
	}

}
