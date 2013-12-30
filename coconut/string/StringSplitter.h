//
//  StringSplitter.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/02.
//
//

#ifndef __coconut__StringSplitter__
#define __coconut__StringSplitter__

#include <vector>
#include <string>

namespace coconut {
  
	class StringSplitter {
	private:
		
		std::vector<std::string> _tokens;
		
		void split(const char* str, const char* seps, bool enableEmpty);
		
	public:
		
		StringSplitter(const char* str, const char* seps, bool enableEmpty = true);
		StringSplitter(const std::string& str, const char* seps, bool enableEmpty = true);
		
		const std::string& get(int idx) const {
			return _tokens[idx];
		}
		const std::vector<std::string>& get() const {
			return _tokens;
		}
		
	};
	
}

#endif /* defined(__coconut__StringSplitter__) */
