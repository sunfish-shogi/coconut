//
//  ResouceLoader.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#ifndef __coconut__ResouceLoader__
#define __coconut__ResouceLoader__

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include "cocos2d.h"

namespace coconut {
	
	template <class T>
	class ResouceLoader {
	private:
		
		typedef std::vector<T> ResouceList;
		typedef std::unordered_map<std::string, ResouceList> PreloadMap;
		typedef std::unordered_map<size_t, int> LoadCounter;
		
		ResouceList _commonResouces;
		PreloadMap _preloadMap;
		LoadCounter _preloadCounter;
		const char* _autoUnloadSceneName;
		bool _prepared;
		
		void load(ResouceList& preloadList, int count = 1) {
			for (auto ite = preloadList.begin(); ite != preloadList.end(); ite++) {
				size_t key = std::hash<T>()(*ite);
				CCASSERT(_preloadCounter[key] >= 0, "invalid status.");
				if (_preloadCounter[key] == 0) {
					onLoad(*ite);
				}
				_preloadCounter[key] += count;
			}
		}
		void unload(ResouceList& preloadList, int count = 1) {
			for (auto ite = preloadList.begin(); ite != preloadList.end(); ite++) {
				size_t key = std::hash<T>()(*ite);
				_preloadCounter[key] -= count;
				CCASSERT(_preloadCounter[key] >= 0, "invalid status.");
				if (_preloadCounter[key] == 0) {
					onUnload(*ite);
				}
			}
		}
		
	protected:
		
		virtual void onLoad(const T& resource) = 0;
		virtual void onUnload(const T& resource) = 0;
		
	public:
		
		ResouceLoader() : _autoUnloadSceneName(nullptr), _prepared(false) {
		}
		~ResouceLoader() {
		}
		
		void addCommonResouce(const T& resouce) {
			_commonResouces.push_back(resouce);
			_prepared = false;
		}
		void addResouce(const char* sceneName, const T& resouce) {
			_preloadMap[sceneName].push_back(resouce);
		}
		void prepare() {
			load(_commonResouces, INT_MAX / 2);
			_prepared = true;
		}
		void load(const char* sceneName, bool autoUnload) {
			if (!_prepared) {
				prepare();
			}
			load(_preloadMap[sceneName]);
			if (_autoUnloadSceneName != nullptr) {
				unload(_autoUnloadSceneName);
			}
			if (autoUnload) {
				_autoUnloadSceneName = sceneName;
			}
		}
		void unload(const char* sceneName) {
			if (!_prepared) {
				prepare();
			}
			unload(_preloadMap[sceneName]);
		}
		
	};
	
}

#endif /* defined(__coconut__ResouceLoader__) */
