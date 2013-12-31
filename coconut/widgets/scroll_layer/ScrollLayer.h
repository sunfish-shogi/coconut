//
//  ScrollLayer.h
//
//  Created by Kubo Ryosuke on 13/09/10.
//
//

#ifndef __coconut__ScrollLayer__
#define __coconut__ScrollLayer__

#include "../../finger_gestures/FingerGesture.h"

namespace coconut {
	
	namespace _ScrollDirection {
		enum Type { NONE, VERTICAL, HORIZONTAL, BOTH };
	}
	typedef _ScrollDirection::Type ScrollDirection;
	
	class ScrollLayer : public cocos2d::Layer {
	private:
		
		cocos2d::Size _viewSize;
		cocos2d::Rect _contentRect;
		bool _enableX;
		bool _enableY;
		cocos2d::Rect _range;
		
		bool _enableOverscrollBounce;
		float _slipperiness;
		float _defaultScrollDuration;
		
		bool _clipping;
		cocos2d::ClippingNode* _clipper;
		cocos2d::DrawNode* _stencil;
		cocos2d::Layer* _content;
		
		FingerGesture _fingerGesture;
		
		cocos2d::Point _velocity;
		struct {
			bool enable;
			float duration;
			float curr;
			cocos2d::Point start;
			cocos2d::Point end;
		} _scrollSchedule;
		
		void setScrollDirection(ScrollDirection direction);
		void updateContentRange(bool keepPosition = false);
		void initStencil();
		
		void update(float delta) override;
		void move(const cocos2d::Point& contentPos, bool overscroll = false);
		void scroll(const cocos2d::Point& contentPos, float duration);
		
		cocos2d::Point normalizedPosition(const cocos2d::Point& pos, bool overscroll = false) const;
		cocos2d::Point getContentPosition(const cocos2d::Point& visiblePos) const;
		cocos2d::Rect getVisibleRect(const cocos2d::Point& contentPos) const;
		cocos2d::Point validateVelocity(const cocos2d::Point& velocity) const;
		
		void moveWithReduction(const cocos2d::Point& velocity);
		void stopAutoScroll();
		
	protected:
		
	public:
		
		ScrollLayer();
		virtual ~ScrollLayer() {}
		
		bool init(const cocos2d::Size& viewSize, const cocos2d::Rect& contentRect,
							ScrollDirection direction = ScrollDirection::VERTICAL,
							bool clipping = true);
		
		static ScrollLayer* create(const cocos2d::Size& viewSize, const cocos2d::Rect& contentRect,
															 ScrollDirection direction = ScrollDirection::VERTICAL,
															 bool clipping = true);
		static ScrollLayer* createFullScreen(const cocos2d::Rect& contentRect,
																				 ScrollDirection direction = ScrollDirection::VERTICAL,
																				 bool clipping = false);
		
		void setEnableOverscrollBounce(bool enable) {
			_enableOverscrollBounce = enable;
		}
		bool isEnableOverscrollBounce() const {
			return _enableOverscrollBounce;
		}
		void setSlipperiness(float value) {
			CCASSERT(value > 0.0f, "slipperiness must be greater than 0.");
			_slipperiness = value;
		}
		float getSlipperiness() const {
			return _slipperiness;
		}
		float getDefaultScrollDuration() const {
			return _defaultScrollDuration;
		}
		void setDefaultScrollDuration(float duration) {
			CCASSERT(duration > 0.0f, "defaultScrollDuration must be greater than 0.");
			_defaultScrollDuration = duration;
		}
		bool isEnableHScroll() const {
			return _enableX;
		}
		bool isEnableVScroll() const {
			return _enableY;
		}
		const cocos2d::Size& getViewSize() const {
			return _viewSize;
		}
		const cocos2d::Rect& getContentRect() const {
			return _contentRect;
		}
		void resizeView(const cocos2d::Size& viewSize) {
			_viewSize = viewSize;
			updateContentRange(true);
			initStencil();
		}
		void resizeContent(const cocos2d::Rect& contentRect) {
			_contentRect = contentRect;
			updateContentRange(true);
		}
		bool isOverscrolled() const;
		bool isOverscrolledX() const;
		bool isOverscrolledY() const;
		float overscrollReductionX() const;
		float overscrollReductionY() const;
		
		void showAt(const cocos2d::Point& pos);
		void showTopLeftCorner();
		void showTopRightCorner();
		void showBottomLeftCorner();
		void showBottomRightCorner();
		void showCenter();
		
		void scrollTo(const cocos2d::Point& pos) {
			scrollTo(pos, _defaultScrollDuration);
		}
		void scrollTo(const cocos2d::Point& pos, float duration) {
			scroll(getContentPosition(pos), duration);
		}
		
		cocos2d::Rect getVisibleRect() const;
		
		cocos2d::Point getTopLeftCorner();
		cocos2d::Point getTopRightCorner();
		cocos2d::Point getBottomLeftCorner();
		cocos2d::Point getBottomRightCorner();
		cocos2d::Point getCenter();
		
		// callbacks
		virtual void slScrolled() {}
		virtual void slDetouch(const cocos2d::Point& position) {}
		virtual void slFlickWithDetouch(const cocos2d::Point& start,
																		const cocos2d::Point& velocity);
			
		// overrides
		virtual void addChild(cocos2d::Node * child) override {
			_content->addChild(child);
		}
		virtual void addChild(Node * child, int zOrder) override {
			_content->addChild(child, zOrder);
		}
		virtual void addChild(Node* child, int zOrder, int tag) override {
			_content->addChild(child, zOrder, tag);
		}
		cocos2d::Node* getChildByTag(int tag) {
			return _content->getChildByTag(tag);
		}
		virtual cocos2d::Array* getChildren() override {
			return _content->getChildren();
		}
		virtual const cocos2d::Array *getChildren() const override {
			return _content->getChildren();
		}
		unsigned int getChildrenCount() const {
			return _content->getChildrenCount();
		}
		virtual void removeChild(Node* child, bool cleanup = true) override {
			_content->removeChild(child, cleanup);
		}
		virtual void removeChildByTag(int tag, bool cleanup = true) override {
			_content->removeChildByTag(tag, cleanup);
		}
		virtual void removeAllChildren() override {
			_content->removeAllChildren();
		}
		virtual void removeAllChildrenWithCleanup(bool cleanup) override {
			_content->removeAllChildrenWithCleanup(cleanup);
		}
		virtual void reorderChild(cocos2d::Node * child, int zOrder) override {
			_content->reorderChild(child, zOrder);
		}
		virtual void sortAllChildren() override {
			_content->sortAllChildren();
		}
		
	};
	
}

#endif /* defined(__coconut__ScrollLayer__) */
