//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//

#ifndef _____PROJECTNAME________FILEBASENAME___View__
#define _____PROJECTNAME________FILEBASENAME___View__

#include "cocos2d.h"
#include <coconut/EventEmitter.hpp>
#include <coconut/scene/SceneChanger.hpp>

namespace ___VARIABLE_namespace___ {

	class ___FILEBASENAME___Model;

	class ___FILEBASENAME___View {

		// event emitters
//		DEFINE_EVENT_EMITTER(/* event name */);

	private:

		___FILEBASENAME___Model* _model;
		cocos2d::Scene* _scene;

	protected:

	public:
		
		___FILEBASENAME___View();
		virtual ~___FILEBASENAME___View();
		void setModel(___FILEBASENAME___Model* model) {
			_model = model;
		}
		void init(cocos2d::Scene* scene);
		
	};

}

#endif /* defined(_____PROJECTNAME________FILEBASENAME___View__) */
