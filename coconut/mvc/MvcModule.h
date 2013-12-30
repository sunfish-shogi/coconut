//
//  MvcModule.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/16.
//
//

#ifndef coconut_Scene_h
#define coconut_Scene_h

#include "cocos2d.h"
#include "../scene/SceneChanger.hpp"
#include "../Module.hpp"
#include "../EventEmitter.hpp"

namespace coconut {
	
	class ExtendedScene;
	
	class MvcModule : public Module {
	private:
		
		ExtendedScene* _scene;
		
	protected:
		
		MvcModule(const char* sceneName);
		virtual ~MvcModule();
		
	public:
		
		cocos2d::Scene* scene();
		
		void onEnter(const std::function<void ()>& callback);
		void onEnterTransFinish(const std::function<void ()>& callback);
		void onExit(const std::function<void ()>& callback);
		void onExitTransStart(const std::function<void ()>& callback);
		void onDestroy(const std::function<void ()>& callback);
		
		void start(const SceneChanger& sceneChanger);
		
	};

}

#endif
