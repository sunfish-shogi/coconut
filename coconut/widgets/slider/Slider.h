//
//  Slider.h
//	coconut
//
//  Created by Kubo Ryosuke on 2013/09/25.
//
//

#ifndef __coconut__Slider__
#define __coconut__Slider__

#include "../../actions/EaseBuilder.h"

namespace coconut {
	
	class Slider : public cocos2d::Node {
	private:
		
		float _value;
		float _minValue;
		float _maxValue;
		
	protected:
		
		virtual void refresh() = 0;
		virtual void refreshWithScroll(float duration, const EaseBuilder& easeBuilder) = 0;
		
	public:
		
		Slider() : _value(0.0f), _minValue(0.0f), _maxValue(1.0f) {
		}
		
		void setValue(float value) {
			_value = value;
			refresh();
		}
		void setValueWithScroll(float value, float duration) {
			setValueWithScroll(value, duration, EaseBuilders::Linear());
		}
		void setValueWithScroll(float value, float duration, const EaseBuilder& easeBuilder) {
			_value = value;
			refreshWithScroll(duration, easeBuilder);
		}
		float getValue() const {
			return _value;
		}
		
		float getMinValue() const {
			return _minValue;
		}
		float getMaxValue() const {
			return _maxValue;
		}
		void setMinValue(float value) {
			_minValue = value;
			refresh();
		}
		void setMaxValue(float value) {
			_maxValue = value;
			refresh();
		}
		void setRange(float minValue, float maxValue) {
			_minValue = minValue;
			_maxValue = maxValue;
			refresh();
		}
		float rate() const {
			if (_maxValue == _minValue) {
				return 1.0f;
			}
			return MIN(MAX((_value - _minValue) / (_maxValue - _minValue), 0.0f), 1.0f);
		}
		
	};
	
}

#endif /* defined(__coconut__Slider__) */
