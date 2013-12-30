//
//  ScaleToX.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/29.
//
//

#ifndef __coconut__ScaleToX__
#define __coconut__ScaleToX__

#include "cocos2d.h"

namespace coconut {

	class ScaleToX : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static ScaleToX* create(float duration, float scale);
		
    /** initializes the action */
    bool initWithDuration(float duration, float scale);
		
    //
    // Overrides
    //
    virtual ScaleToX* clone() const override;
		virtual ScaleToX* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		float _start;
		float _previous;
		float _scale;
	};
	
}

#endif /* defined(__coconut__ScaleToX__) */
