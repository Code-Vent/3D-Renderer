#ifndef UEE_RESOURCE_UTILS_H
#define UEE_RESOURCE_UTILS_H

#include"../Core/core.h"

using namespace uee::core;

namespace uee
{
	namespace utils
	{

		void AddResourceFromFile(const char* dir, const char* filename, UEEresource_types t,
			UEEresource_mode m);
	}
}



#endif