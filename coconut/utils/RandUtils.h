//
//  RandUtils.h
//  coconut
//
//  Created by Kubo Ryosuke on 2014/01/27.
//
//

#ifndef coconut_RandUtils_h
#define coconut_RandUtils_h

#include "../random/Random.h"
#include <string>
#include <sstream>
#include <cassert>

namespace coconut {
  
	class RandUtils {
	private:
		
		RandUtils();
		
	public:
		
		static std::string stringLower(int length) {
			return string<true, false, false>(length);
		}
		static std::string stringUpper(int length) {
			return string<false, true, false>(length);
		}
		static std::string stringAlpha(int length) {
			return string<true, true, false>(length);
		}
		static std::string stringNumber(int length) {
			return string<false, false, true>(length);
		}
		static std::string stringLowerNum(int length) {
			return string<true, false, true>(length);
		}
		static std::string stringUpperNum(int length) {
			return string<false, true, true>(length);
		}
		static std::string stringAlphaNum(int length) {
			return string<true, true, true>(length);
		}
		
		template <bool lower, bool upper, bool number>
		static std::string string(int length) {
			RandomInt r(0, (lower?26:0) + (upper?26:0) + (number?10:0) - 1);
			std::ostringstream oss;
			for (; length > 0; length--) {
				int val = r();
				if (lower) {
					if (val < 26) {
						oss << (char)('a' + val);
						continue;
					}
					val -= 26;
				}
				if (upper) {
					if (val < 26) {
						oss << (char)('A' + val);
						continue;
					}
					val -= 26;
				}
				// otherwise
				assert(number && val < 10);
				oss << (char)('0' + val);
			}
			return oss.str();
		}
		
	};
	
}

#endif
