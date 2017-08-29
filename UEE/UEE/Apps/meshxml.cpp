#include"meshxml.h"
#include"../Utils/utils.h"

using namespace uee::utils;

void AddMeshXmlToResourcesFromObjFile(const char* dir,
	const char* filename)
{
	AddResourceFromFile(dir, filename,
		UEEresource_types::UEE_MESH, UEEresource_mode::UEE_OBJ);
}

/*FILE* GenerateMeshXml(const char* dir, const char* filename)
{
	FILE* file = 0;
	return file;
}*/