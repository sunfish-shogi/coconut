//
//  Vibrate.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#ifndef __coconut__Vibrate__
#define __coconut__Vibrate__

#include "cocos2d.h"

namespace coconut {

	class Vibrate : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static Vibrate* create(float duration, float angle, float amplitude, float frequency);
		
    /** initializes the action */
    bool initWithDuration(float duration, float angle, float amplitude, float frequency);
		
    //
    // Overrides
    //
    virtual Vibrate* clone() const override;
		virtual Vibrate* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		cocos2d::Point _startPosition;
		cocos2d::Point _previousPosition;
		float _angle;
		float _amplitude;
		float _frequency;
		cocos2d::Point position(float t) const;
	};
	
}

#endif /* defined(__coconut__Vibrate__) */
