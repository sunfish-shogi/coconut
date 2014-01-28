//
//  ObjectContainer.h
//  Created by Suguru Namura on 2013/08/27.
//

#ifndef __ObjectContainer__
#define __ObjectContainer__

#include <functional>
#include <list>
#include <unordered_map>
#include <iostream>
#include "Singleton.hpp"

namespace coconut {

	class IObjectDeleter {
	public:
		virtual void clean(void*) = 0;
	};
	
	template <class T>
	class ObjectDeleter : public IObjectDeleter {
	public:
		virtual void clean(void* p) {
			delete static_cast<T*>(p);
			delete this;
		}
	};
	
	/**
	 @brief ObjectContainer which can hold instances.
	 */
	class ObjectContainer
	{
	private:
		
		struct Object {
			void* instance;
			IObjectDeleter* deleter;
		};
		
		// instance map
		std::unordered_map<std::string, Object> map;
		
		ObjectContainer() {
			std::cout << "ObjectContainer: create" << std::endl;
		}
		
		virtual ~ObjectContainer() {
			std::cout << "ObjectContainer: destroy" << std::endl;
		}
		
	public:
		
		/**
		 @brief get global instance
		 */
		static ObjectContainer* global() {
			static ObjectContainer instance;
			return &instance;
		}
		
		/**
		 @brief create local instance
		 */
		static ObjectContainer* createContainer() {
			return new ObjectContainer();
		}
		
		/**
		 @brief delete local instance
		 */
		static void releaseContainer(ObjectContainer* container) {
			if (container != global()) {
				delete container;
			} else {
				std::cout << "ObjectContainer: could not delete global instance." << std::endl;
			}
		}
		
		/**
		 @brief register instance to specific type.
		 @param instance intance to be registered as specified interface.
		 @tparam I interface type
		 */
		template<class I>
		void add(I* item)
		{
			if (this != global() && std::is_base_of<Singleton, I>::value) {
				global()->add(item);
			} else {
				const std::type_info& info = typeid(I);
				std::string name = info.name();
				if (map.count(name) == 0) {
					std::cout << "ObjectContainer: add " << name << std::endl;
					Object object = { item, new ObjectDeleter<I>() };
					map.insert(std::pair<std::string, Object>(name, std::move(object)));
				} else {
					std::cout << "ObjectContainer: " << info.name() << " is already exists." << std::endl;
				}
			}
		}
		
		/**
		 @brief register instance to specific type.
		 @tparam I interface type which is automatically instantiated
		 */
		template<class I>
		I* add()
		{
			I* item = new I();
			this->add(item);
			return item;
		}
		
		template<class I>
		I* find()
		{
			const std::type_info& info = typeid(I);
			std::string key = info.name();
			auto ite = map.find(key);
			if (ite != map.end()) {
				return static_cast<I*>((*ite).second.instance);
			}
			return nullptr;
		}
		
		/**
		 @brief get instance which registered as specific interface.
		 @tparam I interface type
		 */
		template<class I>
		I* get(bool onlyExsiting = false)
		{
			I* item = find<I>();
			if (item != nullptr) {
				return item;
			} else if (this != global()) {
				I* item = global()->find<I>();
				if (item != nullptr) {
					return item;
				}
			}
			return onlyExsiting ? nullptr : add<I>();
		}
		
		/**
		 @brief remove instance from registered map.
		 */
		template<class I>
		void remove()
		{
			const std::type_info& info = typeid(I);
			const char* name = info.name();
			// delete instance
			try {
				Object& object = map.at(name);
				object.deleter->clean(object.instance);
				map.erase(name);
			} catch (std::out_of_range e) {
				// ignore
			}
		}
		
		/**
		 @brief inject registered instance to specific method
		 */
		template<class I, class Arg>
		void inject(void(I::*setter)(Arg*))
		{
			const std::type_info& argtype = typeid(Arg);
			const std::type_info& type = typeid(I);
			
			std::cout << "ObjectContainer: inject " << type.name() << " <- " << argtype.name() << std::endl;
			
			I* item = get<I>(true);
			Arg* arg = get<Arg>(false);
			
			if (item != nullptr && arg != nullptr)
			{
				(item->*setter)(arg);
			}
		};
		
		/**
		 @brief inject with setter method
		 */
		template<class I, class Arg>
		void inject(std::function<void (I*, Arg*)> setter)
		{
			const std::type_info& argtype = typeid(Arg);
			const std::type_info& type = typeid(I);
			
			I* item = static_cast<I*>(map.at(type.name()).instance);
			Arg* arg = static_cast<Arg*>(map.at(argtype.name()).instance);
			
			// inject target setter
			setter(item, arg);
		};
		
		/**
		 @brief get the count which are registered in this container.
		 @return count of the instances.
		 */
		size_t size()
		{
			return map.size();
		}
		
	};
	
};

#endif /* defined(__ObjectContainer__) */
