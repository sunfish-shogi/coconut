//
//  ToggleButton.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/11.
//
//

#ifndef __coconut__ToggleButton__
#define __coconut__ToggleButton__

#include "Button.h"

namespace coconut {
  
	class ToggleButton : public Button {
		
		DEFINE_EVENT_EMITTER(Changed);
		
	private:
		
		int _current;
		std::vector<ButtonSprite*> _sprites;
		void addOneItem(ButtonSprite* sprite);
		
	protected:
		
		virtual ButtonSprite* targetNode();
		
		// overrides
		virtual void btDetouchedInside() override;
		
	public:
		
		virtual bool init() override;
		virtual bool init(const std::vector<ButtonSprite*> sprites);
		virtual bool init(ButtonSprite* sprite, va_list);
		
		void addItem(const std::vector<ButtonSprite*> sprites);
		void addItem(ButtonSprite* sprite, ...) CC_REQUIRES_NULL_TERMINATION;
		void addItem(ButtonSprite* sprite, va_list);
		
		void addItemWithSprite(cocos2d::Node* sprite, cocos2d::Node* touchingSprite = nullptr);
		void addItemWithSpriteFileName(const char* sprite, const char* touchingSprite = nullptr);
		void addItemWithSpriteFrameName(const char* sprite, const char* touchingSprite = nullptr);
		void addItemWithSpriteFrame(cocos2d::SpriteFrame* sprite, cocos2d::SpriteFrame* touchingSprite = nullptr);
		
		int getCurrentIndex() const {
			return _current;
		}
		int getAllItemNum() const {
			return _sprites.size();
		}
		void setCurrentIndex(int index, bool enableCallback = false);
		
		static ToggleButton* create();
		static ToggleButton* create(const std::vector<ButtonSprite*> sprites);
		static ToggleButton* create(ButtonSprite* sprite, ...) CC_REQUIRES_NULL_TERMINATION;
		
	};
	
}

#endif /* defined(__coconut__ToggleButton__) */
