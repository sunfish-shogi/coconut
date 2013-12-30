//
//  EaseBuilder.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/10.
//
//

#ifndef __coconut__EaseBuilder__
#define __coconut__EaseBuilder__

#include "cocos2d.h"

namespace coconut {
	
	class EaseBuilder {
	public:
		virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const = 0;
	};
	
	namespace EaseBuilders {
			
		class Linear : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return action;
			}
		};
		
		class In : public EaseBuilder {
		private:
			float _fRate;
		public:
			In(float fRate) : _fRate(fRate) {}
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseIn::create(action, _fRate);
			}
		};
		
		class Out : public EaseBuilder {
		private:
			float _fRate;
		public:
			Out(float fRate) : _fRate(fRate) {}
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseOut::create(action, _fRate);
			}
		};
		
		class InOut : public EaseBuilder {
		private:
			float _fRate;
		public:
			InOut(float fRate) : _fRate(fRate) {}
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseInOut::create(action, _fRate);
			}
		};
		
		class ExponentialIn : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseExponentialIn::create(action);
			}
		};
		
		class ExponentialOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseExponentialOut::create(action);
			}
		};
			
		class ExponentialInOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseExponentialInOut::create(action);
			}
		};
			
		class SineIn : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseSineIn::create(action);
			}
		};
		
		class SineOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseSineOut::create(action);
			}
		};
	
		class SineInOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseSineInOut::create(action);
			}
		};
	
		class ElasticIn : public EaseBuilder {
		private:
			float _fPeriod;
		public:
			ElasticIn(float fPeriod = 0.3f) : _fPeriod(fPeriod) {}
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseElasticIn::create(action, _fPeriod);
			}
		};
		
		class ElasticOut : public EaseBuilder {
		private:
			float _fPeriod;
		public:
			ElasticOut(float fPeriod = 0.3f) : _fPeriod(fPeriod) {}
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseElasticOut::create(action, _fPeriod);
			}
		};
		
		class ElasticInOut : public EaseBuilder {
		private:
			float _fPeriod;
		public:
			ElasticInOut(float fPeriod = 0.3f) : _fPeriod(fPeriod) {}
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseElasticInOut::create(action, _fPeriod);
			}
		};
		
		class BounceIn : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseBounceIn::create(action);
			}
		};
		
		class BounceOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseBounceOut::create(action);
			}
		};
	
		class BounceInOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseBounceInOut::create(action);
			}
		};
	
		class BackIn : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseBackIn::create(action);
			}
		};
		
		class BackOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseBackOut::create(action);
			}
		};
	
		class BackInOut : public EaseBuilder {
		public:
			virtual cocos2d::ActionInterval* build(cocos2d::ActionInterval* action) const override {
				return cocos2d::EaseBackInOut::create(action);
			}
		};
		
	};
	
}

#endif /* defined(__coconut__EaseBuilder__) */
