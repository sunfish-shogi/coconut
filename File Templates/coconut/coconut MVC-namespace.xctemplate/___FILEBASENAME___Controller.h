//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//

#ifndef _____PROJECTNAME________FILEBASENAME___Controller__
#define _____PROJECTNAME________FILEBASENAME___Controller__

#include <coconut/Macro.hpp>
#include <coconut/scene/SceneChanger.hpp>

namespace ___VARIABLE_namespace___ {

	class ___FILEBASENAME___View;
	class ___FILEBASENAME___Model;

	class ___FILEBASENAME___Controller {

		// event emitters
//		DEFINE_EVENT_EMITTER(/* event name */);

		PROPERTY(___FILEBASENAME___View*, _view, View);
		PROPERTY(___FILEBASENAME___Model*, _model, Model);

	private:

	protected:

	public:

		___FILEBASENAME___Controller();
		virtual ~___FILEBASENAME___Controller();
		void init();

	};

}

#endif /* defined(_____PROJECTNAME________FILEBASENAME___Controller__) */
