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
		
		class ObjectHolder : public cocos2d::Object {
		private:
			std::vector<cocos2d::Object*> _objects;
		public:
			ObjectHolder() : _objects(0) {
			}
			~ObjectHolder() {
				for (auto ite = _objects.begin(); ite != _objects.end(); ite++) {
					(*ite)->release();
				}
				cocos2d::log("ObjectHolder deleted. (items=%lu)", _objects.size());
			}
			void hold(cocos2d::Object* obj) {
				obj->retain();
				_objects.push_back(obj);
			}
			static ObjectHolder* create() {
				ObjectHolder *instance = new ObjectHolder();
				if (instance) {
					instance->autorelease();
					return instance;
				} else {
					CC_SAFE_DELETE(instance);
					return nullptr;
				}
			}
		};
		
		static void holdInCurrentFrame(cocos2d::Node* node) {
			ObjectHolder* holder = ObjectHolder::create();
			holder->hold(node);
		}
		
		static void holdInCurrentFrame(cocos2d::Node* node1, cocos2d::Node* node2, ...) CC_REQUIRES_NULL_TERMINATION {
			ObjectHolder* holder = ObjectHolder::create();
			holder->hold(node1);
			holder->hold(node2);
			va_list params;
			va_start(params, node2);
			while (true) {
				cocos2d::Node* node = va_arg(params, cocos2d::Node*);
				if (node == nullptr) {
					break;
				}
				holder->hold(node);
			}
			va_end(params);
		}
		
	};
  
}

#endif
