//
//  NodeUtils.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/04.
//
//

#ifndef coconut_NodeUtils_h
#define coconut_NodeUtils_h

#include "cocos2d.h"

namespace coconut {
 
	class NodeUtils {
	private:
		
		NodeUtils() {}
		
	public:
		
		static void replaceParent(cocos2d::Node* target, cocos2d::Node* newParent) {
			replaceParent(target, newParent, target->getZOrder(), target->getTag());
		}
		
		static void replaceParent(cocos2d::Node* target, cocos2d::Node* newParent, int zOrder) {
			replaceParent(target, newParent, zOrder, target->getTag());
		}
			
		static void replaceParent(cocos2d::Node* target, cocos2d::Node* newParent, int zOrder, int tag) {
			target->retain();
			target->getParent()->removeChild(target);
			newParent->addChild(target, zOrder, tag);
			target->release();
		}
		
		static void remove(cocos2d::Node* node) {
			node->getParent()->removeChild(node);
		}
		
	};
  
}

#endif
