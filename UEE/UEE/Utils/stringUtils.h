#ifndef UEE_STRING_UTILS_H
#define UEE_STRING_UTILS_H

#include<string>
using namespace std;

namespace uee
{
	namespace utils
	{
		unsigned MakeString(char* str, char** des, const char* delim = "\n");
	}
}

#endif
