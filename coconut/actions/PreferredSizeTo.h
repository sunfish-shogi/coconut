//
//  PreferredSizeTo.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/12/12.
//
//

#ifndef __coconut__PreferredSizeTo__
#define __coconut__PreferredSizeTo__

#include "cocos2d.h"

namespace coconut {

	class PreferredSizeTo : public cocos2d::ActionInterval
	{
	public:
    /** creates the action */
    static PreferredSizeTo* create(float duration, const cocos2d::Size& size);
		
    /** initializes the action */
    bool initWithDuration(float duration, const cocos2d::Size& size);
		
    //
    // Overrides
    //
    virtual PreferredSizeTo* clone() const override;
		virtual PreferredSizeTo* reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
		
	protected:
		cocos2d::Size _start;
		cocos2d::Size _previous;
		cocos2d::Size _size;
	};
	
}

#endif /* defined(__coconut__PreferredSizeTo__) */
