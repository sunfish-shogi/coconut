//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//

#ifndef _____PROJECTNAME________FILEBASENAME___Controller__
#define _____PROJECTNAME________FILEBASENAME___Controller__

#include <coconut/scene/SceneChanger.hpp>

namespace ___VARIABLE_namespace___ {

	class ___FILEBASENAME___View;
	class ___FILEBASENAME___Model;

	class ___FILEBASENAME___Controller {

		// event emitters
//		DEFINE_EVENT_EMITTER(/* event name */);

	private:

		___FILEBASENAME___View* _view;
		___FILEBASENAME___Model* _model;

	protected:

	public:

		___FILEBASENAME___Controller();
		virtual ~___FILEBASENAME___Controller();
		void setView(___FILEBASENAME___View* view) {
			_view = view;
		}
		void setModel(___FILEBASENAME___Model* model) {
			_model = model;
		}
		void init();

	};

}

#endif /* defined(_____PROJECTNAME________FILEBASENAME___Controller__) */
