//
//  ImageManager.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#ifndef __coconut__ImageManager__
#define __coconut__ImageManager__

#include "ResouceLoader.h"

namespace coconut {
	struct SpriteFrameInfo {
		std::string plist;
		std::string texture;
	};
}

namespace std {
	template <>
	struct hash<coconut::SpriteFrameInfo>
	{
		std::size_t operator () (coconut::SpriteFrameInfo const & key) const {
			return std::hash<std::string>()(key.plist) ^ std::hash<std::string>()(key.texture);
		}
	};
}

namespace coconut {
	
	class SpriteFameLoader : public ResouceLoader<SpriteFrameInfo> {
	protected:
		
		virtual void onLoad(const SpriteFrameInfo& resouce) override final;
		virtual void onUnload(const SpriteFrameInfo& resouce) override final;
		
	};
	
	class TextureLoader : public ResouceLoader<std::string> {
	protected:
		
		virtual void onLoad(const std::string& resouce) override final;
		virtual void onUnload(const std::string& resouce) override final;
		
	};
	
	class ImageManager {
	private:
		
		SpriteFameLoader _spriteFrameLoader;
		TextureLoader _textureLoader;
		
		ImageManager() {
		}
		~ImageManager() {
		}
		
	public:
		
		static ImageManager* getInstance() {
			static ImageManager instance;
			return &instance;
		}
		
		void addCommonSpriteFrame(const char* plist);
		void addCommonSpriteFrame(const char* plist, const char* texture);
		void addSpriteFrame(const char* sceneName, const char* plist);
		void addSpriteFrame(const char* sceneName, const char* plist, const char* texture);
		void addCommonTexture(const char* texture);
		void addTexture(const char* sceneName, const char* texture);
		
		void prepare();
		void load(const char* sceneName, bool autoUnload = true);
		void unload(const char* sceneName);
		
	};
	
};

#endif /* defined(__coconut__ImageManager__) */
