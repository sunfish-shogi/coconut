//
//  MvcBuilder.hpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/04.
//
//

#ifndef __coconut_MvcBuilder_hpp__
#define __coconut_MvcBuilder_hpp__

#include "../Modules.hpp"
#include "MvcModule.h"

namespace coconut {
  
	class MvcBuilder {
	private:
		
		ObjectContainer* _container;
		Modules _modules;
		MvcModule* _mainModule = nullptr;
		bool _prepared = false;
		
		void _prepare() {
			ObjectContainer* container = _container;
			_modules.prepare();
			_mainModule->onDestroy([=]() {ObjectContainer::releaseContainer(container);});
		}
		
	public:
		
		MvcBuilder() {
			_container = ObjectContainer::createContainer();
			_modules.setContainer(_container);
		}
		virtual ~MvcBuilder() {
			if (!_prepared) {
				ObjectContainer::releaseContainer(_container);
			}
		}
		
		template <class T>
		MvcBuilder& setMainModule() {
			_mainModule = _modules.add<T>();
			return (*this);
		}
		
		template <class T>
		MvcBuilder& addSubModule() {
			_modules.add<T>();
			return (*this);
		}
		
		template <class T>
		MvcBuilder& addInstance(T* instance, bool cleanup = true) {
			_container->add(instance, cleanup);
			return (*this);
		}
		
		void prepare(const SceneChanger& sceneChanger) {
			_prepare();
			_mainModule->start(sceneChanger);
			_prepared = true;
		}
		
		cocos2d::Scene* prepareWithNoTransition() {
			_prepare();
			_mainModule->start();
			_prepared = true;
			return _mainModule->scene();
		}
		
	};
	
}

#endif
