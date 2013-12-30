//
//  FileAlias.h
//  coconut
//
//  Created by Kubo Ryosuke on 2013/10/15.
//
//

#ifndef coconut_FileAlias_h
#define coconut_FileAlias_h

#include <string>
#include <unordered_map>

namespace coconut {
	
	class FileAlias {
	private:
		
		std::unordered_map<std::string, std::string> _alias;
		
	public:
		
		const char* resolve(const char* aliasName);
		void add(const char* aliasName, const char* fileName, bool override = false);
		
	};
	
}

#endif
