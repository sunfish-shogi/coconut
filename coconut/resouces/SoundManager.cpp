//
//  SoundManager.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#include "SoundManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

namespace coconut {
	
	void EffectLoader::onLoad(const std::string& resouce) {
		SimpleAudioEngine::getInstance()->preloadEffect(resouce.c_str());
		log("load effect: %s", resouce.c_str());
	}
	
	void EffectLoader::onUnload(const std::string& resouce) {
		SimpleAudioEngine::getInstance()->unloadEffect(resouce.c_str());
		log("unload effect: %s", resouce.c_str());
	}
	
	void BgmLoader::onLoad(const std::string& resouce) {
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(resouce.c_str());
		log("load bgm: %s", resouce.c_str());
	}
	
	void BgmLoader::onUnload(const std::string& resouce) {
		// do nothing
		log("unload bgm: %s", resouce.c_str());
	}
	
	void SoundManager::addCommonEffect(const char* soundFile) {
		_effectLoader.addCommonResouce(_alias.resolve(soundFile));
	}
	
	void SoundManager::addCommonEffects(const char* soundFile, ...) {
		if (soundFile != nullptr) {
			va_list params;
			va_start(params, soundFile);
			_effectLoader.addCommonResouce(_alias.resolve(soundFile));
			while (true) {
				const char* p = va_arg(params, const char*);
				if (p == nullptr) {
					break;
				}
				_effectLoader.addCommonResouce(_alias.resolve(p));
			}
			va_end(params);
		}
	}
	
	void SoundManager::addEffect(const char* sceneName, const char* soundFile) {
		_effectLoader.addResouce(sceneName, _alias.resolve(soundFile));
	}
	
	void SoundManager::addEffects(const char* sceneName, const char* soundFile, ...) {
		if (soundFile != nullptr) {
			va_list params;
			va_start(params, soundFile);
			_effectLoader.addResouce(sceneName, _alias.resolve(soundFile));
			while (true) {
				const char* p = va_arg(params, const char*);
				if (p == nullptr) {
					break;
				}
				_effectLoader.addResouce(sceneName, _alias.resolve(p));
			}
			va_end(params);
		}
	}
	
	void SoundManager::addCommonBgm(const char* soundFile) {
		_bgmLoader.addCommonResouce(_alias.resolve(soundFile));
	}
	
	void SoundManager::addCommonBgms(const char* soundFile, ...) {
		if (soundFile != nullptr) {
			va_list params;
			va_start(params, soundFile);
			_bgmLoader.addCommonResouce(_alias.resolve(soundFile));
			while (true) {
				const char* p = va_arg(params, const char*);
				if (p == nullptr) {
					break;
				}
				_bgmLoader.addCommonResouce(_alias.resolve(p));
			}
			va_end(params);
		}
	}
	
	void SoundManager::addBgm(const char* sceneName, const char* soundFile) {
		_bgmLoader.addResouce(sceneName, _alias.resolve(soundFile));
	}
	
	void SoundManager::addBgms(const char* sceneName, const char* soundFile, ...) {
		if (soundFile != nullptr) {
			va_list params;
			va_start(params, soundFile);
			_bgmLoader.addResouce(sceneName, _alias.resolve(soundFile));
			while (true) {
				const char* p = va_arg(params, const char*);
				if (p == nullptr) {
					break;
				}
				_bgmLoader.addResouce(sceneName, _alias.resolve(p));
			}
			va_end(params);
		}
	}
	
	void SoundManager::prepare() {
		_effectLoader.prepare();
		_bgmLoader.prepare();
	}
	
	void SoundManager::load(const char* sceneName, bool autoUnload) {
		_effectLoader.load(sceneName, autoUnload);
		_bgmLoader.load(sceneName, autoUnload);
	}
	
	void SoundManager::unload(const char* sceneName) {
		_effectLoader.unload(sceneName);
		_bgmLoader.unload(sceneName);
	}
	
	void SoundManager::setVolume(float volume) {
		SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
	}
	
	float SoundManager::getVolume() {
		return SimpleAudioEngine::getInstance()->getEffectsVolume();
	}
	
	unsigned int SoundManager::play(const char* soundFile) {
		if (_enableEffect) {
			return SimpleAudioEngine::getInstance()->playEffect(_alias.resolve(soundFile));
		} else {
			return 0;
		}
	}
	
	void SoundManager::stopAll() {
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	
	void SoundManager::pauseAll() {
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
	
	void SoundManager::resumeAll() {
		if (_enableEffect) {
			SimpleAudioEngine::getInstance()->resumeAllEffects();
		}
	}
	
	void SoundManager::stop(unsigned int soundId) {
		SimpleAudioEngine::getInstance()->stopEffect(soundId);
	}
	
	void SoundManager::pause(unsigned int soundId) {
		SimpleAudioEngine::getInstance()->pauseEffect(soundId);
	}
	
	void SoundManager::resume(unsigned int soundId) {
		if (_enableEffect) {
			SimpleAudioEngine::getInstance()->resumeEffect(soundId);
		}
	}
	
	void SoundManager::enableEffect(bool enable) {
		if (_enableEffect != enable) {
			_enableEffect = enable;
			if (!enable) {
				stopAll();
			}
		}
	}
	
	void SoundManager::setBgmVolume(float volume) {
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
	}
	
	float SoundManager::getBgmVolume() {
		return SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	}
	
	void SoundManager::playBgm(const char* soundFile, bool loop) {
		if (_enableBgm) {
			SimpleAudioEngine::getInstance()->playBackgroundMusic(_alias.resolve(soundFile), loop);
		}
	}
	
	void SoundManager::stopBgm() {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	
	void SoundManager::pauseBgm() {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	
	void SoundManager::resumeBgm() {
		if (_enableBgm) {
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
	
	void SoundManager::enableBgm(bool enable) {
		if (_enableBgm != enable) {
			_enableBgm = enable;
			if (enable) {
				resumeBgm();
			} else {
				pauseBgm();
			}
		}
	}
	
}
