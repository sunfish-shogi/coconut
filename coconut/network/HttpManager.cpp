//
//  HttpManager.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/11/12.
//
//

#include "DefaultHttpEncrypter.h"
#include "HttpManager.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "../string/StringSplitter.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace network;

namespace coconut {
	
	class HttpManager::Request : public Object {
	private:
		HttpManager* _parent;
		HttpRequest* _request;
		Callback _callback;
		std::vector<std::string> _headers;
		void* _encOpt;
		SharedBuffer v2b(const std::vector<char>* v) {
			SharedBuffer ret(v ? v->size() : 0);
			if (v) {
				for (int i = 0; i < v->size(); i++) {
					ret.buffer()[i] = (*v)[i];
				}
			}
			return ret;
		}
		void splitHeaders(const SharedBuffer& sb, std::vector<std::string>& headers) {
			std::string src(sb.buffer(), sb.size());
			StringSplitter splitter(src, "\r\n", false);
			const std::vector<std::string>& lines = splitter.get();
			headers.insert(headers.begin(), lines.begin(), lines.end());
		}
		void encrypt(const char* body, unsigned len) {
			SharedBuffer encBody = _parent->getEncrypter()->encrypt(_headers, body, len, _encOpt);
			if (encBody.size() != 0) {
				_request->setRequestData(encBody.buffer(), encBody.size());
			}
		}
		void decrypt(Response& result) {
			result.body = _parent->getEncrypter()->decrypt(result.header, result.body.buffer(), result.body.size(), _encOpt);
		}
	public:
		Request(HttpManager* parent, const char* url,
						const Callback& callback) : _parent(parent), _callback(callback) {
			_request = new HttpRequest();
			_request->setUrl(url);
			_request->setResponseCallback(this, SEL_HttpResponse(&Request::httpCallback));
		}
		virtual ~Request() {
			if (_parent != nullptr) {
				_parent->removeRequest(this);
			}
			delete _request;
		}
		void addHeader(const std::string& header) {
			_headers.push_back(header);
		}
		void setOption(void* encOpt) {
			_encOpt = encOpt;
		}
		void get() {
			encrypt(nullptr, 0);
			_request->setRequestType(HttpRequest::Type::GET);
			_request->setHeaders(_headers);
			HttpClient::getInstance()->send(_request);
		}
		void post(const char* body, unsigned len) {
			encrypt(body, len);
			_request->setRequestType(HttpRequest::Type::POST);
			_request->setHeaders(_headers);
			HttpClient::getInstance()->send(_request);
		}
		void httpCallback(HttpClient* client, HttpResponse* response) {
			if (_parent != nullptr) {
				Response result;
				result.code = response->getResponseCode();
				splitHeaders(v2b(response->getResponseHeader()), result.header);
				result.error = response->getErrorBuffer();
				result.body = v2b(response->getResponseData());
				decrypt(result);
				_callback(result);
			}
		}
		void detouch() {
			_parent = nullptr;
		}
	};
	
	HttpManager::HttpManager() :
		_encrypter(new DefaultHttpEncrypter()),
		_encDeleter([](IEncripter* e) {delete (DefaultHttpEncrypter*)e;}) {
	}
	
	HttpManager::~HttpManager() {
		for (auto ite = _requests.begin(); ite != _requests.end(); ite++) {
			(*ite)->detouch();
		}
	}
	
	void HttpManager::addRequest(Request* request) {
		_requests.push_back(request);
	}
	
	void HttpManager::removeRequest(const Request* request) {
		for (auto ite = _requests.begin(); ite != _requests.end(); ite++) {
			if ((*ite) == request) {
				_requests.erase(ite);
				break;
			}
		}
	}
	
	void HttpManager::get(const char* url, const Callback& callback, void* encOpt) {
		Request* request = new Request(this, url, callback);
		if (!_contentType.empty()) {
			request->addHeader("Content-Type: " + _contentType);
		}
		request->setOption(encOpt);
		request->get();
		addRequest(request);
	}
	
	void HttpManager::post(const char* url, const char* body, unsigned len, const Callback& callback, void* encOpt) {
		Request* request = new Request(this, url, callback);
		if (!_contentType.empty()) {
			request->addHeader("Content-Type: " + _contentType);
		}
		request->setOption(encOpt);
		request->post(body, len);
		addRequest(request);
	}
	
}
