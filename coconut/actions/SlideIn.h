//
//  SlideIn.h
//  patras
//
//  Created by Kubo Ryosuke on 2013/12/20.
//
//

#ifndef __patras__SlideIn__
#define __patras__SlideIn__

#include "cocos2d.h"

namespace coconut {

	class SlideIn : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static SlideIn* create(float duration, const cocos2d::Point& offset);
    static SlideIn* down(float duration) {
			return create(duration, cocos2d::Point(0, cocos2d::Director::getInstance()->getVisibleSize().height));
		}
    static SlideIn* up(float duration) {
			return create(duration, cocos2d::Point(0, -cocos2d::Director::getInstance()->getVisibleSize().height));
		}
    static SlideIn* left(float duration) {
			return create(duration, cocos2d::Point(-cocos2d::Director::getInstance()->getVisibleSize().width, 0));
		}
    static SlideIn* right(float duration) {
			return create(duration, cocos2d::Point(cocos2d::Director::getInstance()->getVisibleSize().width, 0));
		}
		
    /** initializes the action */
    bool initWithDuration(float duration, const cocos2d::Point& offset);
		
    //
    // Overrides
    //
    virtual SlideIn* clone() const override;
		virtual ActionInterval* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		cocos2d::Point _startPosition;
		cocos2d::Point _previousPosition;
		cocos2d::Point _offset;
		cocos2d::Point position(float t) const;
	};
	
}

#endif /* defined(__patras__SlideIn__) */
