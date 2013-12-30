//
//  SimpleTileView.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/09.
//
//

#ifndef __coconut__SimpleTileView__
#define __coconut__SimpleTileView__

#include "BaseTileView.h"

namespace coconut {
	
	class SimpleTileView : public BaseTileView {
	private:
		
		std::vector<cocos2d::Node*> _elements;
		
		void releaseElements();
		
	protected:
		
		bool init(TileViewType type, const cocos2d::Size& tileSize,
							const cocos2d::Size& viewSize,
							float pageSpace = 0.0f, bool clipping = true);
		
	public:
		
		SimpleTileView();
		virtual ~SimpleTileView();
		
		virtual int tileCount() override final {
			return _elements.size();
		}
		virtual cocos2d::Node* activateTile(int index) override final {
			return _elements[index];
		}
		virtual void hideTile(int index, cocos2d::Node* tile) override final {
			// do nothing
		}
		
		void addElement(cocos2d::Node* node);
		
		static SimpleTileView* create(TileViewType type, const cocos2d::Size& tileSize,
																	const cocos2d::Size& viewSize,
																	float pageSpace = 0.0f, bool clipping = true);
		
	};
	
}

#endif /* defined(__coconut__SimpleTileView__) */
