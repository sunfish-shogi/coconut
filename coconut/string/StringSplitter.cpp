//
//  StringSplitter.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/02.
//
//

#include "StringSplitter.h"
#include <sstream>

namespace coconut {
  
	StringSplitter::StringSplitter(const char* str, const char* seps, bool enableEmpty) {
		split(str, seps, enableEmpty);
	}
	
	StringSplitter::StringSplitter(const std::string& str, const char* seps, bool enableEmpty) {
		split(str.c_str(), seps, enableEmpty);
	}
	
	void StringSplitter::split(const char* str, const char* seps, bool enableEmpty) {
		std::ostringstream oss;
		while (true) {
			bool isEnd = false;
			bool isSep = false;
			
			if ((*str) == '\0') {
				isEnd = true;
			} else {
				for (const char* sep = seps; (*sep) != '\0'; sep++) {
					if ((*str) == (*sep)) {
						isSep = true;
						break;
					}
				}
			}
			
			if (isEnd || isSep) {
				if (enableEmpty || !oss.str().empty()) {
					_tokens.push_back(oss.str());
				}
				oss.str("");
				if (isEnd) {
					break;
				}
			} else {
				oss << (*str);
			}
			str++;
		}
	}
	
}
