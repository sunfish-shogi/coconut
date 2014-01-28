//
//  ChangeZOrder.h
//  patras
//
//  Created by Kubo Ryosuke on 2014/01/28.
//
//

#ifndef __patras__ChangeZOrder__
#define __patras__ChangeZOrder__

#include "cocos2d.h"

namespace coconut {

	class CC_DLL ChangeZOrder : public cocos2d::ActionInstant
	{
	public:
		static ChangeZOrder * create(int zOrder);
		
		virtual void update(float time) override;
		virtual ChangeZOrder* clone() const override;
		virtual ChangeZOrder* reverse() const override;
		
	protected:
    ChangeZOrder(){}
    virtual ~ChangeZOrder(){}
		/** init the action */
		bool init(int zOrder);
		
		int _zOrder;
		
	private:
    CC_DISALLOW_COPY_AND_ASSIGN(ChangeZOrder);
	};
	
}

#endif /* defined(__patras__ChangeZOrder__) */
