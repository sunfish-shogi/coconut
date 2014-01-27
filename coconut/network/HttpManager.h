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
		
		std::unique_ptr<IHttpEncrypter> _encrypter;
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
			_encrypter.reset(new T(), std::default_delete<T>());
		}
		template <class T, class U>
		void setEncrypter(U param) {
			_encrypter.reset(new T(param), std::default_delete<T>());
		}
		IHttpEncrypter* getEncrypter() {
			return _encrypter.get();
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
		
		void get(const char* url, const Callback& callback, void* encOpt = nullptr) {
			get(url, std::vector<std::string>(), callback, encOpt);
		}
		void get(const char* url, const std::vector<std::string>& extHeaders, const Callback& callback, void* encOpt = nullptr);
		void post(const char* url, const char* body, unsigned len, const Callback& callback, void* encOpt = nullptr) {
			post(url, std::vector<std::string>(), body, len, callback, encOpt);
		}
		void post(const char* url, const std::vector<std::string>& extHeaders, const char* body, unsigned len, const Callback& callback, void* encOpt = nullptr);
		
	};
	
}

#endif /* defined(__coconut__HttpManager__) */
