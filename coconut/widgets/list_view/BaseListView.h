//
//  BaseListView.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/09/17.
//
//

#ifndef __coconut__BaseListView__
#define __coconut__BaseListView__

#include "../scroll_layer/ScrollLayer.h"

namespace coconut {
 	
	namespace _ListDirection {
		enum Type { VERTICAL, HORIZONTAL };
	}
	typedef _ListDirection::Type ListDirection;
	
	namespace _ListType {
		enum Type { TILE, PAGE };
	}
	typedef _ListType::Type ListType;
	
	class BaseListView : public ScrollLayer {
	private:
		
		struct Element {
			cocos2d::Node* node;
			int index;
		};
		
		ListDirection _direction;
		ListType _type;
		float _space;
		
		cocos2d::Rect _contentRect;
		std::list<Element> _elements;
		
		int _cacheSize;
		std::list<Element> _cache;
		
		cocos2d::Size getSize(int index);
		cocos2d::Rect getRect(cocos2d::Node* node, int index);
		void pageNearest();
		void pagePrev();
		void pageNext();
		void pageTo(cocos2d::Node* node, int index);
		void refreshBefore(const cocos2d::Rect& visible, const cocos2d::Rect& prev, int index);
		void refreshAfter(const cocos2d::Rect& visible, const cocos2d::Rect& prev, int index, bool force = false);
		bool resize(cocos2d::Node* node, int index);
		void clean(const cocos2d::Rect& visible);
		cocos2d::Node* activateCellOnCache(int index);
		void hideCellOnCache(int index, cocos2d::Node* cell);
		
	protected:
		
		BaseListView() {}
		virtual ~BaseListView() {}
		
		bool init(ListDirection direction, const cocos2d::Size& viewSize,
							ListType type = ListType::TILE, int cacheSize = 0,
							float space = 0.0f, bool clipping = true);
		
		cocos2d::Node* getCell(int index);
		
		// overrides
		virtual void slScrolled() override;
		virtual void slDetouch(const cocos2d::Point& position) override;
		virtual void slFlickWithDetouch(const cocos2d::Point& start,
																		const cocos2d::Point& velocity) override;
		
		// callbacks
		virtual int cellCount() = 0; // number of cells
		virtual cocos2d::Size cellSize(int index) = 0;
		virtual cocos2d::Node* activateCell(int index) = 0;
		virtual void hideCell(int index, cocos2d::Node* cell) = 0;
		
	public:
		
		virtual void refresh();
		
	};
	
}

#endif /* defined(__coconut__BaseListView__) */
