//
//  DefaultHttpEncrypter.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/12.
//
//

#ifndef coconut_DefaultHttpEncrypter_h
#define coconut_DefaultHttpEncrypter_h

#include "IHttpEncrypter.h"

namespace coconut {
	
	class DefaultHttpEncrypter : public IHttpEncrypter {
	public:
		virtual SharedBuffer encrypt(std::vector<std::string>& headers, const char* body, unsigned len, void* option) override final {
			SharedBuffer ret(len);
			memcpy(ret.buffer(), body, len);
			return ret;
		}
		virtual SharedBuffer decrypt(std::vector<std::string>& headers, const char* body, unsigned len, void* option) override final {
			SharedBuffer ret(len);
			memcpy(ret.buffer(), body, len);
			return ret;
		}
	};

}

#endif
