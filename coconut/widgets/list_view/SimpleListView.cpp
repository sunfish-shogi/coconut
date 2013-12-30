//
//  SimpleListView.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/08.
//
//

#include "SimpleListView.h"

USING_NS_CC;

namespace coconut {
	
	SimpleListView::SimpleListView() {
	}
	
	SimpleListView::~SimpleListView() {
		releaseElements();
	}
	
	void SimpleListView::releaseElements() {
		while (_elements.size() != 0) {
			const Element& element = _elements.back();
			element.node->release();
			_elements.pop_back();
		}
	}
	
	bool SimpleListView::init(ListDirection direction, const Size& viewSize,
														ListType type, float space, bool clipping) {
		if (!BaseListView::init(direction, viewSize, type, 0, space, clipping)) {
			return false;
		}
		
		return true;
	}
	
	int SimpleListView::cellCount() {
		return _elements.size();
	}
	
	Size SimpleListView::cellSize(int index) {
		return _elements[index].size;
	}
	
	Node* SimpleListView::activateCell(int index) {
		return _elements[index].node;
	}
	
	void SimpleListView::hideCell(int index, Node* cell) {
		// do nothing
	}

	void SimpleListView::addElement(Node* node, const Size& size) {
		node->retain();
		Element element;
		element.node = node;
		element.size = size;
		_elements.push_back(element);
		refresh();
	}
	
	SimpleListView* SimpleListView::create(ListDirection direction, const Size& viewSize,
																				 ListType type, float space, bool clipping) {
		SimpleListView* instance = new SimpleListView();
		if (instance != nullptr && instance->init(direction, viewSize, type, space, clipping)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}
