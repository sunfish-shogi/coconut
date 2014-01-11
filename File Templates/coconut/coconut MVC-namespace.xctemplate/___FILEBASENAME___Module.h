//
//  ___FILENAME___
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//___COPYRIGHT___
//

#ifndef _____PROJECTNAME________FILEBASENAME___Module__
#define _____PROJECTNAME________FILEBASENAME___Module__

#include "___FILEBASENAME___Controller.h"
#include "___FILEBASENAME___View.h"
#include "___FILEBASENAME___Model.h"
#include <coconut/MVC.hpp>

namespace ___VARIABLE_namespace___ {

	class ___FILEBASENAME___Module : public coconut::MvcModule {
	public:
		
		___FILEBASENAME___Module() : coconut::MvcModule("___FILEBASENAME___") {}
	
		virtual void addModule() final override {
			add<___FILEBASENAME___Model>();
			add<___FILEBASENAME___View>();
			add<___FILEBASENAME___Controller>();
		}
		
		virtual void injectModule() final override {
			inject<___FILEBASENAME___View, ___FILEBASENAME___Model>(&___FILEBASENAME___View::setModel);
			inject<___FILEBASENAME___Controller, ___FILEBASENAME___Model>(&___FILEBASENAME___Controller::setModel);
			inject<___FILEBASENAME___Controller, ___FILEBASENAME___View>(&___FILEBASENAME___Controller::setView);
		}
		
		virtual void prepareModule() final override {
			get<___FILEBASENAME___Model>()->init();
			get<___FILEBASENAME___View>()->init(scene());
			get<___FILEBASENAME___Controller>()->init();
		}
		
	};

}

#endif /* defined(_____PROJECTNAME________FILEBASENAME___Module__) */
