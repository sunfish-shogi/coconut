//
//  Rotate.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/01.
//
//

#ifndef __coconut__Rotate__
#define __coconut__Rotate__

#include "cocos2d.h"

namespace coconut {
	
	class Rotate : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static Rotate* create(float duration, float rps);
		
    /** initializes the action */
    bool initWithDuration(float duration, float rps);
		
    //
    // Overrides
    //
    virtual Rotate* clone() const override;
		virtual Rotate* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		float _startRotation;
		float _previousRotation;
		float _rps;
	};
	
}

#endif /* defined(__coconut__Rotate__) */
