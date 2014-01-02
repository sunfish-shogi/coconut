//
//  HttpManager.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/12.
//
//

#ifndef __coconut__HttpManager__
#define __coconut__HttpManager__

#include "IHttpEncrypter.h"
#include <functional>
#include <string>
#include <list>
#include <vector>

namespace coconut {
	
	class HttpManager {
	private:
		
		class Request;
	
	public:
	
		struct Response {
			int code;
			const char* error;
			std::vector<std::string> header;
			SharedBuffer body;
		};
	
		typedef std::function<void(const Response&)> Callback;
		
	private:
		
		IEncripter* _encrypter;
		std::function<void (IEncripter*)> _encDeleter;
		std::list<Request*> _requests;
		std::string _contentType;
		std::vector<std::string> _commonHeaders;
		
		void addRequest(Request* request);
		void removeRequest(const Request* requst);
		
	public:
		
		HttpManager();
		virtual ~HttpManager();
		
		template <class T>
		void setEncrypter() {
			_encDeleter(_encrypter);
			_encrypter = new T();
			_encDeleter = [](IEncripter* e) {
				delete (T*)e;
			};
		}
		template <class T, class U>
		void setEncrypter(U param) {
			_encDeleter(_encrypter);
			_encrypter = new T(param);
			_encDeleter = [](IEncripter* e) {
				delete (T*)e;
			};
		}
		IEncripter* getEncrypter() {
			return _encrypter;
		}
		
		void setContentType(const char* contentType) {
			_contentType = contentType;
		}
		void setContentType(const std::string& contentType) {
			_contentType = contentType;
		}
		const std::string& getContentType() const {
			return _contentType;
		}
		
		void addCommonHeader(const char* header) {
			_commonHeaders.push_back(header);
		}
		void addCommonHeader(const std::string& header) {
			_commonHeaders.push_back(header);
		}
		
		void get(const char* url, const Callback& callback, void* encOpt = nullptr);
		void post(const char* url, const char* body, unsigned len, const Callback& callback, void* encOpt = nullptr);
		
	};
	
}

#endif /* defined(__coconut__HttpManager__) */
