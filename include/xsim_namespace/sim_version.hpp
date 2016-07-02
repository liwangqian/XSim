#ifndef SIM_VERSION_HPP
#define SIM_VERSION_HPP

namespace version{
	
	//Date Version Types
	static const char DATE[] = "08";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.05";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 4;
	static const long REVISION  = 26;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 153;
	#define RC_FILEVERSION 1,0,4,26
	#define RC_FILEVERSION_STRING "1, 0, 4, 26\0"
	static const char FULLVERSION_STRING [] = "1.0.4.26";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 4;
	

}
#endif //SIM_VERSION_HPP
