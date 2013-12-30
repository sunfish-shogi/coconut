//
//  SimpleListView.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/08.
//
//

#ifndef __coconut__SimpleListView__
#define __coconut__SimpleListView__

#include "BaseListView.h"

namespace coconut {
	
	class SimpleListView : public BaseListView {
	private:
		
		struct Element {
			cocos2d::Node* node;
			cocos2d::Size size;
		};
		
		std::vector<Element> _elements;
		
		void releaseElements();
		
	protected:
		
		bool init(ListDirection direction, const cocos2d::Size& viewSize,
							ListType type = ListType::TILE, float space = 0.0f, bool clipping = true);
		
		virtual int cellCount() override;
		virtual cocos2d::Size cellSize(int index) override;
		virtual cocos2d::Node* activateCell(int index)  override;
		virtual void hideCell(int index, cocos2d::Node* cell) override;
		
	public:
		
		SimpleListView();
		virtual ~SimpleListView();
		
		void addElement(cocos2d::Node* node, const cocos2d::Size& size);
		
		static SimpleListView* create(ListDirection direction, const cocos2d::Size& viewSize,
																	ListType type = ListType::TILE, float space = 0.0f, bool clipping = true);
		
	};
	
}

#endif /* defined(__coconut__SimpleListView__) */
