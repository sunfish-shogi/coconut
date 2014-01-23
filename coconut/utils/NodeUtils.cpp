//
//  NodeUtils.cpp
//  patras
//
//  Created by Kubo Ryosuke on 2014/01/23.
//
//

#include "NodeUtils.h"

USING_NS_CC;

namespace coconut {
  
	namespace {
		
		class ObjectHolder : public Object {
		private:
			std::vector<Object*> _objects;
		public:
			ObjectHolder() : _objects(0) {
			}
			~ObjectHolder() {
				for (auto ite = _objects.begin(); ite != _objects.end(); ite++) {
					(*ite)->release();
				}
				log("ObjectHolder deleted. (items=%lu)", _objects.size());
			}
			void hold(Object* obj) {
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
		
	}
		
	void NodeUtils::holdInCurrentFrame(Node* node) {
		ObjectHolder* holder = ObjectHolder::create();
		holder->hold(node);
	}
	
	void NodeUtils::holdInCurrentFrame(Node* node1, Node* node2, ...) {
		ObjectHolder* holder = ObjectHolder::create();
		holder->hold(node1);
		holder->hold(node2);
		va_list params;
		va_start(params, node2);
		while (true) {
			Node* node = va_arg(params, Node*);
			if (node == nullptr) {
				break;
			}
			holder->hold(node);
		}
		va_end(params);
	}
	
}