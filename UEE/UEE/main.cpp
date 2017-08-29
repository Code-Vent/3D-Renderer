#include<iostream>

#include"Apps\3dviewer.h"
//#include"Utils\utils.h"
//#include"Core\typedefs.h"


int main(int argc, char** argv)
{
	_3DViewerAppInit(&argc, argv, "Resources/Mesh/Mario", "Mario.mesh.xml");
	_3DViewerAppRun();
	atexit(_3DViewerAppShutdown);
	_3DViewerAppShutdown();	
	
	system("PAUSE");
	return 0;
}