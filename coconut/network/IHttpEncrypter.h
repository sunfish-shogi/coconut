//
//  IHttpEncrypter.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/12.
//
//

#ifndef coconut_IHttpEncrypter_h
#define coconut_IHttpEncrypter_h

#include "../memory/SharedBuffer.hpp"
#include <vector>
#include <string>

namespace coconut {

	class IHttpEncrypter {
	public:
		virtual SharedBuffer encrypt(std::vector<std::string>& headers, const char* body, unsigned len, void* option) = 0;
		virtual SharedBuffer decrypt(std::vector<std::string>& headers, const char* body, unsigned len, void* option) = 0;
	};

}

#endif
