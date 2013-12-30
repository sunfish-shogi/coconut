//
//  ScaleToY.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/29.
//
//

#ifndef __coconut__ScaleToY__
#define __coconut__ScaleToY__

#include "cocos2d.h"

namespace coconut {

	class ScaleToY : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static ScaleToY* create(float duration, float scale);
		
    /** initializes the action */
    bool initWithDuration(float duration, float scale);
		
    //
    // Overrides
    //
    virtual ScaleToY* clone() const override;
		virtual ScaleToY* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		float _start;
		float _previous;
		float _scale;
	};
	
}

#endif /* defined(__coconut__ScaleToY__) */
