//
//  CheckBox.h
//
//  Created by Kubo Ryosuke on 13/09/06.
//
//

#ifndef __coconut__CheckBox__
#define __coconut__CheckBox__

#include "cocos2d.h"
#include "../../EventEmitter.hpp"

namespace coconut {
	
	class CheckBox : public cocos2d::Layer {
		
		DEFINE_EVENT_EMITTER(Checked);
		DEFINE_EVENT_EMITTER(Unchecked);
		DEFINE_EVENT_EMITTER(Changed);
	
	public:
		
		class _CheckGroup;
		
	private:
		
		cocos2d::Node* _check;
		cocos2d::Sprite* _background;
		cocos2d::Node* _label;
		bool _value;
		_CheckGroup* _group;
		
	public:
		
		class _CheckGroup : public cocos2d::Object {
			DEFINE_EVENT_EMITTER(Changed);
		private:
			int _value;
			struct Member {
				CheckBox* checkBox;
				int value;
			};
			std::list<Member> _members;
			void uncheck(CheckBox* except);
		public:
			virtual bool init();
			CREATE_FUNC(_CheckGroup);
			void join(CheckBox* checkBox, int value);
			int getValue() const {
				return _value;
			}
			void setValue(int value);
		};
		
	private:
		
		bool init(cocos2d::Node* check, cocos2d::Sprite* background, cocos2d::Node* label);
		bool isEnablePosition(const cocos2d::Point& pos);
		bool isInside(cocos2d::Node* obj, const cocos2d::Point& pos);
		void updateStatus();
		
	public:
		
		CheckBox();
		virtual ~CheckBox();
		
		void setValue(bool value, bool enableCallbacks = false);
		bool getValue() {
			return _value;
		}
		
		bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
		
		static CheckBox* create(cocos2d::Node* check, cocos2d::Sprite* background, cocos2d::Node* label);
		static CheckBox* create(const char* label, const char* fontName, int fontSize);
		
	};
	
	typedef CheckBox::_CheckGroup CheckGroup;
	
}

#endif /* defined(__coconut__CheckBox__) */
