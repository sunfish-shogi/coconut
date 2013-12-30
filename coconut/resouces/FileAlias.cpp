//
//  FileAlias.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#include "FileAlias.h"
#include "cocos2d.h"

USING_NS_CC;

namespace coconut {
	
	const char* FileAlias::resolve(const char* aliasName) {
		auto ite = _alias.find(aliasName);
		return ite != _alias.end() ? (*ite).second.c_str() : aliasName;
	}
	
	void FileAlias::add(const char* aliasName, const char* fileName, bool override) {
		if (override || _alias.find(aliasName) == _alias.end()) {
			_alias[aliasName] = fileName;
		} else {
			CCASSERT(false, "such alias already exists.");
		}
	}
	
}
