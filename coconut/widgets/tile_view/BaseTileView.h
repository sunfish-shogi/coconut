//
//  TileView.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/09.
//
//

#ifndef __coconut__TileView__
#define __coconut__TileView__

#include "../list_view/BaseListView.h"

namespace coconut {
	
	namespace _TileViewType {
		enum Type {
			Horizontal,
			Vertical,
			HorizontalPage,
			VerticalPage,
		};
	}
	typedef _TileViewType::Type TileViewType;
	
	class BaseTileView : public BaseListView {
	private:
		
		class Box : public cocos2d::Node {
		public:
			std::vector<cocos2d::Node*> elements;
			CREATE_FUNC(Box);
		};
		
		cocos2d::Size _boxSize;
		cocos2d::Size _tileSize;
		int _columns;
		int _rows;
		int _cellsPerBox;
		int _prevLastIndex;
		
		cocos2d::Point getTilePosition(int idx) const;
		
		void refresh(int index);
		
	protected:
		
		bool init(TileViewType type, const cocos2d::Size& tileSize,
							const cocos2d::Size& viewSize,
							float pageSpace = 0.0f,
							int cacheSize = 0, bool clipping = true);
		
		// overrides
		virtual int cellCount() override final {
			return (tileCount() + _cellsPerBox - 1) / _cellsPerBox;
		}
		virtual cocos2d::Size cellSize(int index) override final {
			return _boxSize;
		}
		virtual cocos2d::Node* activateCell(int index) override final;
		virtual void hideCell(int index, cocos2d::Node* cell) override final;
		
		// callbacks
		virtual int tileCount() = 0;
		virtual cocos2d::Node* activateTile(int index) = 0;
		virtual void hideTile(int index, cocos2d::Node* tile) = 0;
		
	public:
		
		virtual void refresh() override;
		
	};
	
}

#endif /* defined(__coconut__TileView__) */
