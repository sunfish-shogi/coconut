//
//  ImageManager.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#include "ImageManager.h"
#include "cocos2d.h"

USING_NS_CC;

namespace coconut {
	
	void SpriteFameLoader::onLoad(const SpriteFrameInfo& resouce) {
		if (resouce.texture.empty()) {
			log("load sprite frame: %s", resouce.plist.c_str());
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(resouce.plist.c_str());
		} else {
			log("load sprite frame: %s: %s", resouce.plist.c_str(), resouce.texture.c_str());
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(resouce.plist.c_str(), resouce.texture.c_str());
		}
	}
	
	void SpriteFameLoader::onUnload(const SpriteFrameInfo& resouce) {
		log("unload sprite frame: %s", resouce.plist.c_str());
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(resouce.plist.c_str());
	}
	
	void TextureLoader::onLoad(const std::string& resouce) {
		log("load texture: %s", resouce.c_str());
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(resouce.c_str());
    if (!fullpath.empty()) {
			Image* image = new Image();
			if (image->initWithImageFile(fullpath.c_str())) {
				Director::getInstance()->getTextureCache()->addImage(image, resouce.c_str());
			}
			CC_SAFE_DELETE(image);
		}
	}
	
	void TextureLoader::onUnload(const std::string& resouce) {
		log("unload texture: %s", resouce.c_str());
		Director::getInstance()->getTextureCache()->removeTextureForKey(resouce.c_str());
	}
	
	void ImageManager::addCommonSpriteFrame(const char* plist) {
		addCommonSpriteFrame(plist, "");
	}
		
	void ImageManager::addCommonSpriteFrame(const char* plist, const char* texture) {
		SpriteFrameInfo info;
		info.plist = plist;
		info.texture = texture;
		_spriteFrameLoader.addCommonResouce(info);
	}
	
	void ImageManager::addSpriteFrame(const char* sceneName, const char* plist) {
		addSpriteFrame(sceneName, plist, "");
	}
		
	void ImageManager::addSpriteFrame(const char* sceneName, const char* plist, const char* texture) {
		SpriteFrameInfo info;
		info.plist = plist;
		info.texture = texture;
		_spriteFrameLoader.addResouce(sceneName, info);
	}
	
	void ImageManager::addCommonTexture(const char* texture) {
		_textureLoader.addCommonResouce(texture);
	}
	
	void ImageManager::addTexture(const char* sceneName, const char* texture) {
		_textureLoader.addResouce(sceneName, texture);
	}
	
	void ImageManager::prepare() {
		_spriteFrameLoader.prepare();
		_textureLoader.prepare();
	}
	
	void ImageManager::load(const char* sceneName, bool autoUnload) {
		_spriteFrameLoader.load(sceneName, autoUnload);
		_textureLoader.load(sceneName, autoUnload);
	}
	
	void ImageManager::unload(const char* sceneName) {
		_spriteFrameLoader.unload(sceneName);
		_textureLoader.unload(sceneName);
	}
	
}
