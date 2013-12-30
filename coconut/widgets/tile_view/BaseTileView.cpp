//
//  TileView.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/09.
//
//

#include "BaseTileView.h"

USING_NS_CC;

namespace coconut {
	
	bool BaseTileView::init(TileViewType type, const cocos2d::Size& tileSize,
													const Size& viewSize, float pageSpace,
													int cacheSize, bool clipping) {
		ListDirection listDirection;
		ListType listType;
		float space;
		
		switch (type) {
			case TileViewType::Horizontal:
				listDirection = ListDirection::HORIZONTAL;
				listType = ListType::TILE;
				space = 0.0f;
				_columns = 1;
				_rows = (int)(viewSize.height / tileSize.height);
				_boxSize = Size(tileSize.width, viewSize.height);
				break;
			case TileViewType::Vertical:
				listDirection = ListDirection::VERTICAL;
				listType = ListType::TILE;
				space = 0.0f;
				_columns = (int)(viewSize.width / tileSize.width);
				_rows = 1;
				_boxSize = Size(viewSize.width, tileSize.height);
				break;
			case TileViewType::HorizontalPage:
				listDirection = ListDirection::HORIZONTAL;
				listType = ListType::PAGE;
				space = pageSpace;
				_columns = (int)(viewSize.width / tileSize.width);
				_rows = (int)(viewSize.height / tileSize.height);
				_boxSize = viewSize;
				break;
			case TileViewType::VerticalPage:
				listDirection = ListDirection::VERTICAL;
				listType = ListType::PAGE;
				space = pageSpace;
				_columns = (int)(viewSize.width / tileSize.width);
				_rows = (int)(viewSize.height / tileSize.height);
				_boxSize = viewSize;
				break;
			default:
				CCASSERT(false, "invalid TileViewType.");
		}
		
		_cellsPerBox = _columns * _rows;
		_tileSize = tileSize;
		_prevLastIndex = 0;
		
		CCASSERT(_columns > 0, "invalid settings.");
		CCASSERT(_rows > 0, "invalid settings.");
		CCASSERT(_cellsPerBox > 0, "invalid settings.");
		
		if (!BaseListView::init(listDirection, viewSize, listType, cacheSize, space, clipping)) {
			return false;
		}
		
		return true;
	}
	
	Node* BaseTileView::activateCell(int index) {
		int startIndex = index * _cellsPerBox;
		int num = MIN(_cellsPerBox, tileCount() - startIndex);
		Box* box = Box::create();
		for (int i = 0; i < num; i++) {
			Node* element = activateTile(startIndex + i);
			box->elements.push_back(element);
			element->setPosition(getTilePosition(i));
			box->addChild(element);
		}
		return box;
	}
	
	void BaseTileView::hideCell(int index, Node* cell) {
		int startIndex = index * _cellsPerBox;
		Box* box = (Box*)cell;
		for (int i = 0; i < box->elements.size(); i++) {
			Node* element = box->elements[i];
			hideTile(startIndex + i, element);
		}
	}
	
	Point BaseTileView::getTilePosition(int idx) const {
		float col = idx % _columns + 0.5;
		float row = _rows - idx / _columns - 0.5;
		return Point(_tileSize.width * col, _tileSize.height * row) - (Point)_boxSize * 0.5f;
	}
	
	void BaseTileView::refresh() {
		int lastIndex = cellCount() - 1;
		BaseListView::refresh();
		refresh(_prevLastIndex);
		if (lastIndex != _prevLastIndex) {
			refresh(lastIndex);
			_prevLastIndex = lastIndex;
		}
	}
	
	void BaseTileView::refresh(int index) {
		int startIndex = index * _cellsPerBox;
		int num = MIN(_cellsPerBox, tileCount() - startIndex);
		Box* box = (Box*)getCell(index);
		if (box != nullptr) {
			for (int i = box->elements.size(); i < num; i++) {
				Node* element = activateTile(startIndex + i);
				box->elements.push_back(element);
				element->setPosition(getTilePosition(i));
				box->addChild(element);
			}
			for (int i = box->elements.size() - 1; i >= num; i--) {
				Node* element = box->elements[i];
				hideTile(startIndex + i, element);
				box->removeChild(element);
				box->elements.pop_back();
			}
		}
	}
	
}
