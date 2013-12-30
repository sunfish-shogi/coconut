//
//  SoundManager.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#ifndef __coconut__SoundManager__
#define __coconut__SoundManager__

#include "ResouceLoader.h"
#include "FileAlias.h"
#include "cocos2d.h"

namespace coconut {
	
	class EffectLoader : public ResouceLoader<std::string> {
	protected:
		
		virtual void onLoad(const std::string& resouce) override final;
		virtual void onUnload(const std::string& resouce) override final;
		
	};
	
	class BgmLoader : public ResouceLoader<std::string> {
	protected:
		
		virtual void onLoad(const std::string& resouce) override final;
		virtual void onUnload(const std::string& resouce) override final;
		
	};
	
	class SoundManager {
	private:
		
		EffectLoader _effectLoader;
		BgmLoader _bgmLoader;
		FileAlias _alias;
		bool _enableEffect;
		bool _enableBgm;
		
		SoundManager() : _enableEffect(true), _enableBgm(true) {
		}
		~SoundManager() {
		}
		
	public:
		
		static SoundManager* getInstance() {
			static SoundManager instance;
			return &instance;
		}
		
		void alias(const char* aliasName, const char* fileName, bool override = false) {
			_alias.add(aliasName, fileName, override);
		}
		
		void addCommonEffect(const char* soundFile);
		void addCommonEffects(const char* soundFile, ...) CC_REQUIRES_NULL_TERMINATION;
		void addEffect(const char* sceneName, const char* soundFile);
		void addEffects(const char* sceneName, const char* soundFile, ...) CC_REQUIRES_NULL_TERMINATION;
		
		void addCommonBgm(const char* soundFile);
		void addCommonBgms(const char* soundFile, ...) CC_REQUIRES_NULL_TERMINATION;
		void addBgm(const char* sceneName, const char* soundFile);
		void addBgms(const char* sceneName, const char* soundFile, ...) CC_REQUIRES_NULL_TERMINATION;
		
		void prepare();
		void load(const char* sceneName, bool autoUnload = true);
		void unload(const char* sceneName);
		
		void setVolume(float volume);
		float getVolume();
		unsigned int play(const char* soundFile);
		void stopAll();
		void pauseAll();
		void resumeAll();
		void stop(unsigned int soundId);
		void pause(unsigned int soundId);
		void resume(unsigned int soundId);
		void enableEffect(bool enable);
	
		void setBgmVolume(float volume);
		float getBgmVolume();
		void playBgm(const char* soundFile, bool loop = false);
		void stopBgm();
		void pauseBgm();
		void resumeBgm();
		void enableBgm(bool enable);
	};
	
};

#endif /* defined(__coconut__SoundManager__) */
