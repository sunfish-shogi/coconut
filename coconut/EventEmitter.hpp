//
//  EventListener.hpp
//  coconut
//
//  Created by Suguru Namura on 2013/08/29.
//
//

#ifndef coconut_EventEmitter_hpp
#define coconut_EventEmitter_hpp

#include <functional>
#include <map>

namespace coconut {
	template <class ... ARG>
	struct EventHandler {
		std::function<void(ARG...)> handler;
		bool once;
	};
}

#define DEFINE_EVENT_EMITTER(NAME) \
private: \
	int _handlerCounter##NAME = 0; \
	std::map<int, coconut::EventHandler<>> _handler##NAME; \
public: \
	int on##NAME(const std::function<void()>& handler) \
	{ \
		int id = _handlerCounter##NAME++; \
		coconut::EventHandler<> eventHandler; \
		eventHandler.handler = handler; \
		eventHandler.once = false; \
		_handler##NAME[id] = eventHandler; \
		return id; \
	}; \
	int once##NAME(const std::function<void()>& handler) \
	{ \
		int id = _handlerCounter##NAME++; \
		coconut::EventHandler<> eventHandler; \
		eventHandler.handler = handler; \
		eventHandler.once = true; \
		_handler##NAME[id] = eventHandler; \
		return id; \
	}; \
	void off##NAME(int id) \
	{ \
\
		_handler##NAME.erase(id); \
	}; \
	void offAll##NAME() { \
		_handler##NAME.clear(); \
	}; \
	void emit##NAME() \
	{ \
\
		for (auto it = _handler##NAME.begin(); it != _handler##NAME.end();) { \
			const coconut::EventHandler<>& eventHandler = it->second; \
			const std::function<void()>& handler = eventHandler.handler; \
			handler(); \
			if (eventHandler.once) { \
				it = _handler##NAME.erase(it); \
			} else { \
				it++; \
			} \
		} \
	};

#define DEFINE_EVENT_EMITTER_WITH_ARG(NAME, ARG) \
private: \
	int _handlerCounter##NAME = 0; \
	std::map<int, coconut::EventHandler<ARG>> _handler##NAME; \
public: \
	int on##NAME(const std::function<void(ARG)>& handler) \
	{ \
		int id = _handlerCounter##NAME++; \
		coconut::EventHandler<ARG> eventHandler; \
		eventHandler.handler = handler; \
		eventHandler.once = false; \
		_handler##NAME[id] = eventHandler; \
		return id; \
	}; \
	int once##NAME(const std::function<void(ARG)>& handler) \
	{ \
		int id = _handlerCounter##NAME++; \
		coconut::EventHandler<ARG> eventHandler; \
		eventHandler.handler = handler; \
		eventHandler.once = true; \
		_handler##NAME[id] = eventHandler; \
		return id; \
	}; \
	void off##NAME(int id) \
	{ \
\
		_handler##NAME.erase(id); \
	}; \
	void offAll##NAME() { \
		_handler##NAME.clear(); \
	}; \
void emit##NAME(ARG arg) \
	{ \
\
		for (auto it = _handler##NAME.begin(); it != _handler##NAME.end();) { \
			const coconut::EventHandler<ARG>& eventHandler = it->second; \
			const std::function<void(ARG)>& handler = eventHandler.handler; \
			handler(arg); \
			if (eventHandler.once) { \
				it = _handler##NAME.erase(it); \
			} else { \
				it++; \
			} \
		} \
	};

#define DEFINE_EVENT_EMITTER_WITH_ARGS2(NAME, ARG1, ARG2) \
private: \
	int _handlerCounter##NAME = 0; \
	std::map<int, coconut::EventHandler<ARG1,ARG2>> _handler##NAME; \
public: \
	int on##NAME(const std::function<void(ARG1,ARG2)>& handler) \
	{ \
		int id = _handlerCounter##NAME++; \
		coconut::EventHandler<ARG1,ARG2> eventHandler; \
		eventHandler.handler = handler; \
		eventHandler.once = false; \
		_handler##NAME[id] = eventHandler; \
		return id; \
}; \
	int once##NAME(const std::function<void(ARG1,ARG2)>& handler) \
	{ \
		int id = _handlerCounter##NAME++; \
		coconut::EventHandler<ARG1,ARG2> eventHandler; \
		eventHandler.handler = handler; \
		eventHandler.once = true; \
		_handler##NAME[id] = eventHandler; \
		return id; \
}; \
	void off##NAME(int id) \
	{ \
\
		_handler##NAME.erase(id); \
	}; \
	void offAll##NAME() { \
		_handler##NAME.clear(); \
	}; \
void emit##NAME(ARG1 arg1, ARG2 arg2) \
	{ \
\
		for (auto it = _handler##NAME.begin(); it != _handler##NAME.end();) { \
			const coconut::EventHandler<ARG1,ARG2>& eventHandler = it->second; \
			const std::function<void(ARG1,ARG2)>& handler = eventHandler.handler; \
			handler(arg1, arg2); \
			if (eventHandler.once) { \
				it = _handler##NAME.erase(it); \
			} else { \
				it++; \
			} \
		}\
	};

#endif
