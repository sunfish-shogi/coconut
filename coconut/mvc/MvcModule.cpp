//
//  MvcModule.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/16.
//
//

#include "MvcModule.h"
#include "../EventEmitter.hpp"
#include "../schedule/ScheduleManager.h"
#include "../resouces/ImageManager.h"
#include "../resouces/SoundManager.h"
#include "../Macro.hpp"

USING_NS_CC;

namespace coconut {
			
	class ExtendedScene : public Scene {
		
		DEFINE_EVENT_EMITTER(Enter);
		DEFINE_EVENT_EMITTER(EnterTransFinish);
		DEFINE_EVENT_EMITTER(Exit);
		DEFINE_EVENT_EMITTER(ExitTransStart);
		DEFINE_EVENT_EMITTER(Destroy);
		
	private:
		
		bool _loaded;
		std::string _name;
		PROPERTY(ScheduleManager*, _scheduleManager, ScheduleManager);
		
	public:
		
		ExtendedScene();
		virtual ~ExtendedScene();
		
		virtual bool init(const char* sceneName);
		
		virtual void onEnter() override;
		virtual void onEnterTransitionDidFinish() override;
		virtual void onExit() override;
		virtual void onExitTransitionDidStart() override;
		
		static ExtendedScene* create(const char* sceneName);
	
	};
	
	ExtendedScene::ExtendedScene() : _loaded(false) {
	}
	
	ExtendedScene::~ExtendedScene() {
		emitDestroy();
		if (_loaded) {
			ImageManager::getInstance()->unload(_name.c_str());
			SoundManager::getInstance()->unload(_name.c_str());
		}
	}
	
	bool ExtendedScene::init(const char* sceneName) {
		if (!Scene::init()) {
			return false;
		}
		
		_name = sceneName;
		
		ImageManager::getInstance()->load(_name.c_str(), false);
		SoundManager::getInstance()->load(_name.c_str(), false);
		_loaded = true;
		
		return true;
	}
	
	void ExtendedScene::onEnter() {
		log("Scene [%s]: onEnter", _name.c_str());
		Scene::onEnter();
		_scheduleManager->resume();
		emitEnter();
	}
	
	void ExtendedScene::onEnterTransitionDidFinish() {
		log("Scene [%s]: onEnterTransitionDidFinish", _name.c_str());
		Scene::onEnterTransitionDidFinish();
		emitEnterTransFinish();
	}
	
	void ExtendedScene::onExit() {
		log("Scene [%s]: onExit", _name.c_str());
		Scene::onExit();
		_scheduleManager->pause();
		emitExit();
	}
		
	void ExtendedScene::onExitTransitionDidStart() {
		log("Scene [%s]: onExitTransitionDidStart", _name.c_str());
		Scene::onExitTransitionDidStart();
		emitExitTransStart();
	}
	
	ExtendedScene* ExtendedScene::create(const char* sceneName) {
		ExtendedScene* instance = new ExtendedScene();
		if (instance != nullptr && instance->init(sceneName)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	MvcModule::MvcModule(const char* sceneName) {
		ExtendedScene* scene = ExtendedScene::create(sceneName);
		_scene = scene;
	}
	
	MvcModule::~MvcModule() {
	}
	
	Scene* MvcModule::scene() {
		return _scene;
	}
	
	void MvcModule::onceEnter(const std::function<void ()>& callback) {
		_scene->onceEnter(callback);
	}
	
	void MvcModule::onceEnterTransFinish(const std::function<void ()>& callback) {
		_scene->onceEnterTransFinish(callback);
	}
	
	void MvcModule::onceExit(const std::function<void ()>& callback) {
		_scene->onceExit(callback);
	}
	
	void MvcModule::onceExitTransStart(const std::function<void ()>& callback) {
		_scene->onceExitTransStart(callback);
	}
	
	void MvcModule::onEnter(const std::function<void ()>& callback) {
		_scene->onEnter(callback);
	}
	
	void MvcModule::onEnterTransFinish(const std::function<void ()>& callback) {
		_scene->onEnterTransFinish(callback);
	}
	
	void MvcModule::onExit(const std::function<void ()>& callback) {
		_scene->onExit(callback);
	}
	
	void MvcModule::onExitTransStart(const std::function<void ()>& callback) {
		_scene->onExitTransStart(callback);
	}
	
	void MvcModule::onDestroy(const std::function<void ()>& callback) {
		_scene->onDestroy(callback);
	}
	
	void MvcModule::start(const SceneChanger& sceneChanger) {
		_scene->setScheduleManager(get<ScheduleManager>());
		sceneChanger.changeTo(_scene);
	}
	
}
