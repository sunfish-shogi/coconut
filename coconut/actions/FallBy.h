//
//  FallBy.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#ifndef __coconut__FallBy__
#define __coconut__FallBy__

#include "cocos2d.h"

namespace coconut {

	class FallBy : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static FallBy* create(float duration, const cocos2d::Point& initialVelocity, float gravity);
		
    /** initializes the action */
    bool initWithDuration(float duration, const cocos2d::Point& initialVelocity, float gravity);
		
    //
    // Overrides
    //
    virtual FallBy* clone() const override;
		virtual FallBy* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		cocos2d::Point _startPosition;
		cocos2d::Point _previousPosition;
		cocos2d::Point _initialVelocity;
		float _gravity;
		cocos2d::Point position(float t) const;
	};
	
}

#endif /* defined(__coconut__FallBy__) */
