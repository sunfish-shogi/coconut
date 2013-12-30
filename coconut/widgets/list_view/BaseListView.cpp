//
//  BaseListView.cpp
//  coconut
//
//  Created by Kubo Ryosuke on 2013/09/17.
//
//

#include "BaseListView.h"
#include <cfloat>

USING_NS_CC;

namespace coconut {
	
	bool BaseListView::init(ListDirection direction, const Size& viewSize,
													ListType type, int cacheSize, float space, bool clipping) {
		ScrollDirection scrollDir;
		switch (direction) {
			case ListDirection::HORIZONTAL:
				scrollDir = ScrollDirection::HORIZONTAL;
				break;
			case ListDirection::VERTICAL:
				scrollDir = ScrollDirection::VERTICAL;
				break;
			default: CCASSERT(false, "invalid list direction.");
		}
		_direction = direction;
		_type = type;
		_cacheSize = cacheSize;
		_space = space;
		
		_contentRect.origin = Point(0, -viewSize.height);
		_contentRect.size = viewSize;
		
		if (!ScrollLayer::init(viewSize, _contentRect, scrollDir, clipping)) {
			return false;
		}
		
		return true;
	}

	void BaseListView::slScrolled() {
		refresh();
	}
	
	void BaseListView::slDetouch(const Point& position) {
		if (_type == ListType::PAGE) {
			pageNearest();
		}
	}
		
	void BaseListView::slFlickWithDetouch(const Point& start, const Point& velocity) {
		switch (_type) {
			case ListType::TILE:
				ScrollLayer::slFlickWithDetouch(start, velocity);
				break;
			case ListType::PAGE:
				switch (_direction) {
					case ListDirection::HORIZONTAL:
						if (velocity.x <= 0.0f) {
							pageNext();
						} else {
							pagePrev();
						}
						break;
					case ListDirection::VERTICAL:
						if (velocity.y >= 0.0f) {
							pageNext();
						} else {
							pagePrev();
						}
						break;
					default:
						CCASSERT(false, "invalid direction.");
				}
				break;
			default:
				CCASSERT(false, "invalid list type.");
		}
	}
	
	void BaseListView::pageNearest() {
		const Rect& visibleRect = getVisibleRect();
		const Point visibleCenter(visibleRect.getMidX(), visibleRect.getMidY());
		Element* element = nullptr;
		float distance = FLT_MAX;
		for (auto ite = _elements.begin(); ite != _elements.end(); ite++) {
			float d = visibleCenter.getDistance((*ite).node->getPosition());
			if (d < distance) {
				element = &(*ite);
				distance = d;
			}
		}
		if (element != nullptr) {
			pageTo(element->node, element->index);
		}
	}
		
	void BaseListView::pagePrev() {
		if (!_elements.empty()) {
			pageTo(_elements.front().node, _elements.front().index);
		}
	}
	
	void BaseListView::pageNext() {
		if (!_elements.empty()) {
			pageTo(_elements.back().node, _elements.back().index);
		}
	}
	
	void BaseListView::pageTo(Node* node, int index) {
		const Rect& rect = getRect(node, index);
		scrollTo(Point(rect.getMinX(), rect.getMinY()), 0.3f);
	}
	
	Size BaseListView::getSize(int index) {
		switch (_type) {
			case ListType::TILE:
				return cellSize(index);
			case ListType::PAGE:
				return getViewSize();
			default:
				CCASSERT(false, "invalid list type.");
		}
	}
	
	Rect BaseListView::getRect(Node* node, int index) {
		const Point& pos = node->getPosition();
		const Size& size = getSize(index);
		return Rect(pos.x - size.width / 2.0f, pos.y - size.height / 2.0f,
								size.width, size.height);
	}
	
	void BaseListView::refresh() {
		const Rect& visible = getVisibleRect();
		bool topOk = false;
		bool endOk = false;
		int topIdx, endIdx;
		Rect top, end;
		
		if (!_elements.empty()) {
			top = getRect(_elements.front().node, _elements.front().index);
			end = getRect(_elements.back().node, _elements.back().index);
			topOk = top.intersectsRect(visible);
			endOk = end.intersectsRect(visible);
			topIdx = _elements.front().index;
			endIdx = _elements.back().index;
		}
		
		// clean
		clean(visible);
		
		if (!topOk && !endOk) {
			Rect topLeft = Rect::ZERO;
			topLeft.origin = getTopLeftCorner();
			refreshAfter(visible, topLeft, -1, true);
		} else {
			if (topOk) {
				refreshBefore(visible, top, topIdx);
			}
			if (endOk) {
				refreshAfter(visible, end, endIdx);
			}
		}
		
		// resize
		bool resized = false;
		if (!_elements.empty()) {
			resized |= resize(_elements.front().node, _elements.front().index);
			if (_elements.size() != 1) {
				resized |= resize(_elements.back().node, _elements.back().index);
			}
		}
		if (resized) {
			resizeContent(_contentRect);
		}
	}
		
	void BaseListView::refreshBefore(const Rect& visible, const Rect& prev, int index) {
		Rect r = prev;
		for (index--; index >= 0; index--) {
			const Size& size = getSize(index);
			float space = (!r.size.equals(Size::ZERO) ? _space : 0.0f);
			if (_direction == ListDirection::HORIZONTAL) {
				r = Rect(r.origin.x - (size.width + space),
								 r.getMaxY() - size.height,
								 size.width,
								 size.height);
			} else {
				r = Rect(r.origin.x,
								 r.origin.y + (r.size.height + space),
								 size.width,
								 size.height);
			}
			if (visible.intersectsRect(r)) {
				Element element;
				element.index = index;
				element.node = activateCellOnCache(index);
				_elements.push_front(element);
	
				element.node->setPosition(Point(r.getMidX(), r.getMidY()));
			} else {
				return;
			}
		}
	}
	
	void BaseListView::refreshAfter(const Rect& visible, const Rect& prev, int index, bool force) {
		Rect r = prev;
		for (index++; index < cellCount(); index++) {
			const Size& size = getSize(index);
			float space = (!r.size.equals(Size::ZERO) ? _space : 0.0f);
			if (_direction == ListDirection::HORIZONTAL) {
				r = Rect(r.origin.x + (r.size.width + space),
								 r.getMaxY() - size.height,
								 size.width,
								 size.height);
			} else {
				r = Rect(r.origin.x,
								 r.origin.y - (size.height + space),
								 size.width,
								 size.height);
			}
			if (visible.intersectsRect(r)) {
				Element element;
				element.index = index;
				element.node = activateCellOnCache(index);
				_elements.push_back(element);
	
				element.node->setPosition(Point(r.getMidX(), r.getMidY()));
			} else if (!force) {
				return;
			}
		}
	}
	
	bool BaseListView::resize(Node* node, int index) {
		Rect rect = getRect(node, index);
		Rect prev = _contentRect;
		switch (_direction) {
			case ListDirection::HORIZONTAL:
				if (index == 0) {
					_contentRect.origin.x = rect.getMinX();
				} else {
					_contentRect.origin.x = MIN(_contentRect.origin.x, rect.getMinX() - (_space + 1.0f));
				}
				_contentRect.size.width += prev.origin.x - _contentRect.origin.x;
				
				if (index == cellCount() - 1) {
					_contentRect.size.width = rect.getMaxX() - _contentRect.origin.x;
				} else {
					_contentRect.size.width = MAX(_contentRect.size.width, rect.getMaxX() - _contentRect.origin.x + (_space + 1.0f));
				}
				break;
			case ListDirection::VERTICAL:
				if (index == cellCount() - 1) {
					_contentRect.origin.y = rect.getMinY();
				} else {
					_contentRect.origin.y = MIN(_contentRect.origin.y, rect.getMinY() - (_space + 1.0f));
				}
				_contentRect.size.height += prev.origin.y - _contentRect.origin.y;
				
				if (index == 0) {
					_contentRect.size.height = rect.getMaxY() - _contentRect.origin.y;
				} else {
					_contentRect.size.height = MAX(_contentRect.size.height, rect.getMaxY() - _contentRect.origin.y + (_space + 1.0f));
				}
				break;
			default:
				CCASSERT(false, "invalid direction.");
		}
		return !_contentRect.equals(prev);
	}
	
	void BaseListView::clean(const Rect& visible) {
		enum { BEFORE, VISIBLE, AFTER } state = BEFORE;
		for (auto ite = _elements.begin(); ite != _elements.end();) {
			bool erase = false;
			if ((*ite).index >= cellCount()) {
				erase= true;
			} else if (state == AFTER) {
				erase = true;
			} else if (visible.intersectsRect(getRect(ite->node, ite->index))) {
				state = VISIBLE;
			} else {
				erase = true;
				if (state == VISIBLE) { state = AFTER; }
			}
			if (erase) {
				hideCellOnCache(ite->index, ite->node);
				ite = _elements.erase(ite);
				continue;
			}
			ite++;
		}
	}
	
	Node* BaseListView::activateCellOnCache(int index) {
		for (auto ite = _cache.begin(); ite != _cache.end(); ite++) {
			Element element = (*ite);
			if (element.index == index) {
				_cache.erase(ite);
				return element.node;
			}
		}
		Node* node = activateCell(index);
		addChild(node);
		return node;
	}
	
	void BaseListView::hideCellOnCache(int index, Node* cell) {
		Element element;
		element.index = index;
		element.node = cell;
		_cache.push_front(element);
		while (_cache.size() > _cacheSize) {
			Element& old = _cache.back();
			hideCell(old.index, old.node);
			removeChild(old.node);
			_cache.pop_back();
		}
	}
	
	Node* BaseListView::getCell(int index) {
		for (auto ite = _elements.begin(); ite != _elements.end(); ite++) {
			if ((*ite).index == index) {
				return (*ite).node;
			}
		}
		for (auto ite = _cache.begin(); ite != _cache.end(); ite++) {
			if ((*ite).index == index) {
				return (*ite).node;
			}
		}
		return nullptr;
	}
	
};
