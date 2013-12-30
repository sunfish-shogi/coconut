//
//  Module.hpp
//  coconut
//
//  Created by Suguru Namura on 2013/09/18.
//
//

#ifndef __coconut_Module_hpp__
#define	__coconut_Module_hpp__

#include "ObjectContainer.hpp"

namespace coconut {

	/**
	 @brief Module is the set of defintions to register instances to the ObjectContainer.
	 */
	class Module
	{
	private:
		
		ObjectContainer* _container;
		
	protected:
	
		Module() {
			_container = ObjectContainer::global();
		}
		
		/**
		 @brief Add instance to the container.
		 @param instance
		 */
		template<class T>
		void add(T* instance)
		{
			_container->add(instance);
		}
		
		/**
		 @brief Add class to the container. Container will instantiate the class immediately.
		 */
		template<class T>
		void add()
		{
			_container->add<T>();
		}
		
		/**
		 @brief Get the registered instance of the class.
		 @return instance.
		 */
		template<class T>
		T* get()
		{
			return _container->get<T>();
		}
		
		/**
		 @brief Inject setter method.
		 @param setter function pointer of the setter.
		 */
		template<class I, class Arg>
		void inject(void(I::*setter)(Arg*))
		{
			_container->inject(setter);
		}
		
		/**
		 @brief Inject setter method.
		 @param setter function.
		 */
		template<class I, class Arg>
		void inject(std::function<void (I*, Arg*)> setter)
		{
			_container->inject(setter);
		}
		
	public:
		
		virtual ~Module() {
		}
		
		void setContainer(ObjectContainer* container) {
			_container = container;
		}
		
		/**
		 @param Add module.
		 */
		virtual void addModule() = 0;
		
		/**
		 @param Inject module. This method should be overriden by children.
		 */
		virtual void injectModule() = 0;
		
		/**
		 @param Prepare module. This method will be called after injection.
		 */
		virtual void prepareModule() = 0;
		
	};

}
#endif
