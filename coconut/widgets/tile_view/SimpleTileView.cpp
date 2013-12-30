//
//  SimpleTileView.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/09.
//
//

#include "SimpleTileView.h"

USING_NS_CC;

namespace coconut {
	
	SimpleTileView::SimpleTileView() {
	}
	
	SimpleTileView::~SimpleTileView() {
		releaseElements();
	}
	
	void SimpleTileView::releaseElements() {
		while (_elements.size() != 0) {
			_elements.back()->release();
			_elements.pop_back();
		}
	}
	
	bool SimpleTileView::init(TileViewType type,
														const Size& tileSize,
														const Size& viewSize,
														float pageSpace,
														bool clipping) {
		if (!BaseTileView::init(type, tileSize, viewSize, pageSpace, 0, clipping)) {
			return false;
		}
		
		return true;
	}
	
	void SimpleTileView::addElement(Node* node) {
		node->retain();
		_elements.push_back(node);
		refresh();
	}
	
	SimpleTileView* SimpleTileView::create(TileViewType type,
																				 const Size& tileSize,
																				 const Size& viewSize,
																				 float pageSpace,
																				 bool clipping) {
		SimpleTileView* instance = new SimpleTileView();
		if (instance != nullptr && instance->init(type, tileSize, viewSize, pageSpace, clipping)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
}
