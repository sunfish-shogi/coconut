//
//  Modules.hpp
//  BaseGame
//
//  Created by Suguru Namura on 2013/09/18.
//
//

#ifndef __coconut_Modules_hpp__
#define __coconut_Modules_hpp__

#include "Module.hpp"
#include <vector>
#include <type_traits>

namespace coconut {
	
	/**
	 @brief Modules is the utility to initialize and inject Module instances.
	 */
	class Modules
	{
	private:
		
		ObjectContainer* _container;
		std::vector<Module*> list;
		
	public:
		
		Modules()
		{
			_container = ObjectContainer::global();
		}
		
		~Modules()
		{
			destroy();
		}
		
		void setContainer(ObjectContainer* container) {
			_container = container;
		}
		
		/**
		 @brief Add module to the registry.
		 */
		template<class T>
		T* add()
		{
			static_assert(std::is_base_of<Module, T>::value, "T should be a base of Module.");
			T* module = new T();
			list.push_back(static_cast<Module*>(module));
			module->setContainer(_container);
			return module;
		}
		
		/**
		 @brief Inject added modules
		 */
		void prepare()
		{
			for (Module* module : list)
			{
				module->addModule();
			}
			for (Module* module : list)
			{
				module->injectModule();
			}
			for (Module* module : list)
			{
				module->prepareModule();
			}
		}
		
		/**
		 @brief Clear modules. This method should be called after inject.
		 */
		void destroy()
		{
			// destruct modules
			for (Module* module : list) {
				delete module;
			}
			list.clear();
		}
	};
	
}

#endif
