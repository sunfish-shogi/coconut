//
//  ScrollLayer.cpp
//
//  Created by Kubo Ryosuke on 13/09/10.
//
//

#include "ScrollLayer.h"
#include "../../Utils/ArrayUtils.h"
#include "../../Utils/GeomUtils.h"

USING_NS_CC;

#define CURB(a, b)							(std::max(std::min((a), (b)), -(b)))

namespace {
	std::function<void ()> DEFAULT_CALLBACK = []() {};
}

namespace coconut {
	
	ScrollLayer::ScrollLayer() :
	_enableOverscrollBounce(false),
	_slipperiness(1.0f),
	_defaultScrollDuration(1.0f) {
	}
	
	bool ScrollLayer::init(const Size& viewSize, const Rect& contentRect,
												 ScrollDirection direction, bool clipping) {
		if (!GestureLayer::init()) {
			return false;
		}
		_clipping = clipping;
		_viewSize = viewSize;
		_contentRect = contentRect;
		
		setContentSize(viewSize);
		
		_content = Layer::create();
		if (_clipping) {
			_clipper = ClippingNode::create();
			GestureLayer::addChild(_clipper, 0, 0);
			_clipper->addChild(_content);
		} else {
			GestureLayer::addChild(_content, 0, 0);
		}
		
		setScrollDirection(direction);
		updateContentRange();
		initStencil();
		
		stopAutoScroll();
		scheduleUpdate();
		
		return true;
	}
	
	void ScrollLayer::initStencil() {
		if (_clipping) {
			_stencil = DrawNode::create();
			Point verts[] = {
				Point(0.0f, 0.0f),
				Point(_viewSize.width, 0.0f),
				Point(_viewSize.width,  _viewSize.height),
				Point(0.0f,  _viewSize.height),
			};
			_stencil->drawPolygon(verts, ARRAY_SIZE(verts), Color4F(1, 1, 1, 1), 1, Color4F(1, 1, 1, 1));

			_clipper->setStencil(_stencil);
		}
	}
	
	void ScrollLayer::setScrollDirection(ScrollDirection direction) {
		switch (direction) {
			case ScrollDirection::NONE:
				_enableX = false;
				_enableY = false;
				break;
				
			case ScrollDirection::HORIZONTAL:
				_enableX = true;
				_enableY = false;
				break;
				
			case ScrollDirection::VERTICAL:
				_enableX = false;
				_enableY = true;
				break;
				
			case ScrollDirection::BOTH:
				_enableX = true;
				_enableY = true;
				break;
				
			default:
				break;
		}
	}
	
	void ScrollLayer::updateContentRange(bool keepPosition) {
		_range.origin.x = -(_contentRect.origin.x + MAX(0.0f, _contentRect.size.width - _viewSize.width));
		_range.origin.y = -(_contentRect.origin.y + _contentRect.size.height - _viewSize.height);
		_range.size.width = (_enableX ? MAX(0.0f, _contentRect.size.width - _viewSize.width) : 0.0f);
		_range.size.height = (_enableY ? MAX(0.0f, _contentRect.size.height - _viewSize.height) : 0.0f);
		if (keepPosition) {
			move(_content->getPosition(), _enableOverscrollBounce);
		} else {
			move(-_contentRect.origin);
		}
	}
		
	Point ScrollLayer::normalizedPosition(const Point& pos, bool overscroll) const {
		if (overscroll) {
			return Point(_enableX ? pos.x : MAX(_range.getMinX(), MIN(_range.getMaxX(), pos.x)),
									 _enableY ? pos.y : MAX(_range.getMinY(), MIN(_range.getMaxY(), pos.y)));
		} else {
			return Point(MAX(_range.getMinX(), MIN(_range.getMaxX(), pos.x)),
									 MAX(_range.getMinY(), MIN(_range.getMaxY(), pos.y)));
		}
	}
	
	bool ScrollLayer::isOverscrolled() const {
		return !_range.containsPoint(_content->getPosition());
	}
		
	bool ScrollLayer::isOverscrolledX() const {
		const Point& contentPos = _content->getPosition();
		return !(contentPos.x >= _range.getMinX() && contentPos.x <= _range.getMaxX());
	}
	
	bool ScrollLayer::isOverscrolledY() const {
		const Point& contentPos = _content->getPosition();
		return !(contentPos.y >= _range.getMinY() && contentPos.y <= _range.getMaxY());
	}
	
#define REDUCTION(overWidth, viewWidth) (MAX(0.5f-0.7f*(overWidth)/(viewWidth), 0.0f))
	float ScrollLayer::overscrollReductionX() const {
		const Point& contentPos = _content->getPosition();
		if (contentPos.x < _range.getMinX()) {
			return REDUCTION(_range.getMinX()-contentPos.x, _viewSize.width);
		} else if (contentPos.x > _range.getMaxX()) {
			return REDUCTION(contentPos.x-_range.getMaxX(), _viewSize.width);
		}
		return 1.0f;
	}
	
	float ScrollLayer::overscrollReductionY() const {
		const Point& contentPos = _content->getPosition();
		if (contentPos.y < _range.getMinY()) {
			return REDUCTION(_range.getMinY()-contentPos.y, _viewSize.height);
		} else if (contentPos.y > _range.getMaxY()) {
			return REDUCTION(contentPos.y-_range.getMaxY(), _viewSize.height);
		}
		return 1.0f;
	}
#undef REDUCTION
	
	void ScrollLayer::update(float delta) {
		if (_scrollSchedule.enable) {
			// auto scroll
			_scrollSchedule.curr += delta;
			Point diff = _scrollSchedule.end - _scrollSchedule.start;
			float d = MIN(_scrollSchedule.curr / _scrollSchedule.duration, 1.0f);
			move(_scrollSchedule.start - diff * (cosf(M_PI * d) - 1) * 0.5f, _enableOverscrollBounce);
			if (d == 1.0f) { stopAutoScroll(); }
		} else {
			Point pos = _content->getPosition();
			const Point& posN = normalizedPosition(pos);
			float reduction = powf(1.0e-2f, delta / _slipperiness);
			float reductionOS = powf(1.0e-12f, delta / _slipperiness);
			float bounce = powf(1.0e-4f, delta / _slipperiness);
			// X
			if (fabsf(_velocity.x) > 10.f) {
				// flick
				if (!isOverscrolledX()) {
					_velocity.x = _velocity.x * reduction;
				} else {
					_velocity.x = CURB(_velocity.x, 500.0f);
					_velocity.x = _velocity.x * reductionOS;
				}
				pos.x += _velocity.x * delta;
			} else if (isOverscrolledX() && getTouchCount() == 0) {
				// bounce
				pos.x = posN.x + (pos.x - posN.x) * bounce;
			}
			// Y
			if (fabsf(_velocity.y) > 10.f) {
				// flick
				if (!isOverscrolledY()) {
					_velocity.y = _velocity.y * reduction;
				} else {
					_velocity.y = CURB(_velocity.y, 500.0f);
					_velocity.y = _velocity.y * reductionOS;
				}
				pos.y += _velocity.y * delta;
			} else if (isOverscrolledY() && getTouchCount() == 0) {
				// bounce
				pos.y = posN.y + (pos.y - posN.y) * bounce;
			}
			move(pos, _enableOverscrollBounce);
		}
	}
		
	GestureResult ScrollLayer::fgTouchBegan(const Point& position) {
		if (position.x >= 0.0f &&
				position.x <= _viewSize.width &&
				position.y >= 0.0f &&
				position.y <= _viewSize.height) {
			stopAutoScroll();
			return GestureResult::OK;
		}
		return GestureResult::UNCAUGHT;
	}
	
	void ScrollLayer::fgMove(const Point& position,
													 const Point& delta) {
		stopAutoScroll();
		Point d = delta;
		d.x *= overscrollReductionX();
		d.y *= overscrollReductionY();
		move(_content->getPosition() + d, _enableOverscrollBounce);
	}
	
	void ScrollLayer::fgDetouch(const cocos2d::Point& position) {
		slDetouch(position);
	}
	
	GestureResult ScrollLayer::fgFlickWithDetouch(const Point& start,
																								const Point& velocity) {
		slFlickWithDetouch(start, velocity);
		return GestureResult::OK;
	}
		
	void ScrollLayer::slFlickWithDetouch(const Point& start,
																			 const Point& velocity) {
		moveWithReduction(velocity);
	}
	
	void ScrollLayer::move(const Point& contentPos, bool overscroll) {
		const Point& pos = normalizedPosition(contentPos, overscroll);
		if (!_content->getPosition().equals(pos)) {
			_content->setPosition(pos);
			slScrolled();
		}
	}
		
	void ScrollLayer::showAt(const Point& pos) {
		stopAutoScroll();
		move(getContentPosition(pos));
	}
	
	void ScrollLayer::showTopLeftCorner() {
		stopAutoScroll();
		return move(getContentPosition(getTopLeftCorner()));
	}
	
	void ScrollLayer::showTopRightCorner() {
		stopAutoScroll();
		return move(getContentPosition(getTopRightCorner()));
	}
	
	void ScrollLayer::showBottomLeftCorner() {
		stopAutoScroll();
		return move(getContentPosition(getBottomLeftCorner()));
	}
	
	void ScrollLayer::showBottomRightCorner() {
		stopAutoScroll();
		return move(getContentPosition(getBottomRightCorner()));
	}
	
	void ScrollLayer::showCenter() {
		stopAutoScroll();
		return move(getContentPosition(getCenter()));
	}
	
	void ScrollLayer::scroll(const Point& contentPos, float duration) {
		stopAutoScroll();
		_scrollSchedule.enable = true;
		_scrollSchedule.duration = duration;
		_scrollSchedule.curr = 0.0f;
		_scrollSchedule.start = _content->getPosition();
		_scrollSchedule.end = contentPos;
	}
	
	void ScrollLayer::moveWithReduction(const Point& velocity) {
		stopAutoScroll();
		_velocity = validateVelocity(velocity);
	}
	
	Point ScrollLayer::validateVelocity(const Point& velocity) const {
		return Point(CURB(velocity.x * overscrollReductionX(), 3000.0f),
								 CURB(velocity.y * overscrollReductionY(), 3000.0f));
	}
		
	void ScrollLayer::stopAutoScroll() {
		_velocity = Point::ZERO;
		_scrollSchedule.enable = false;
	}
	
	Point ScrollLayer::getContentPosition(const Point& visiblePos) const {
		return -visiblePos;
	}
		
	Rect ScrollLayer::getVisibleRect() const {
		const Rect& rect = getVisibleRect(_content->getPosition());
		const Rect& rectN = getVisibleRect(normalizedPosition(_content->getPosition()));
		return rect.unionWithRect(rectN);
	}
	
	Rect ScrollLayer::getVisibleRect(const Point& contentPos) const {
		return Rect(-contentPos.x, -contentPos.y, _viewSize.width, _viewSize.height);
	}
		
	Point ScrollLayer::getTopLeftCorner() {
		return Point(_contentRect.getMinX(), _contentRect.getMaxY());
	}
	
	Point ScrollLayer::getTopRightCorner() {
		return Point(_contentRect.getMaxX(), _contentRect.getMaxY());
	}
	
	Point ScrollLayer::getBottomLeftCorner() {
		return Point(_contentRect.getMinX(), _contentRect.getMinY());
	}
	
	Point ScrollLayer::getBottomRightCorner() {
		return Point(_contentRect.getMaxX(), _contentRect.getMinY());
	}
	
	Point ScrollLayer::getCenter() {
		return Point(_contentRect.getMidX(), _contentRect.getMidY());
	}
	
	ScrollLayer* ScrollLayer::create(const Size& viewSize, const Rect& contentRect,
																	 ScrollDirection direction, bool clipping) {
		ScrollLayer* instance = new ScrollLayer();
		if (instance != nullptr && instance->init(viewSize, contentRect, direction, clipping)) {
			instance->autorelease();
			return instance;
		}
		CC_SAFE_DELETE(instance);
		return nullptr;
	}
	
	ScrollLayer* ScrollLayer::createFullScreen(const Rect& contentRect, ScrollDirection direction, bool clipping) {
		return create(Director::getInstance()->getVisibleSize(), contentRect, direction, clipping);
	}
	
}
