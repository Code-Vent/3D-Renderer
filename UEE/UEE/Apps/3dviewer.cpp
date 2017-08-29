#include"3dviewer.h"

#include"glApplication.h"
using uee::apps::GLApplication;
using uee::apps::GLUTInitParams;

#include"..\Entity\model3D.h"
using uee::entity::Model3D;
#include"..\Graphics\meshInfo.h"
using uee::graphx::Mesh_Info;
#include"..\Graphics\camera.h"
using uee::graphx::Camera;


GLApplication *app = nullptr;

static Vector3 camPos;
static Vector3 camTarget;

Mesh_Info* mesh = nullptr;
Model3D* mdl = nullptr;


Camera *mainCam;

void findCameraTargetAndPosition(Mesh_Info* m, Vector3* target, Vector3* position);

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);	
	glCullFace(GL_BACK);	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mainCam->Update();
	mdl->DrawMesh();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(mainCam->GetProjectionMatrix(w, h));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(mainCam->GetViewMatrix());
}

void _3DViewerAppInit(int *pargc, char *argv[],
	const char* dir, const char* filename)
{
	GLUTInitParams params;
	params.displayMode = GLUT_SINGLE | GLUT_RGB;
	params.width = 512;
	params.height = 512;
	params.x = 100;
	params.y = 100;
	params.pargc = pargc;
	params.pargv = argv;
	params.contextVersionMajor = 3;
	params.contextVersionMinor = 1;
	params.contextProfile = GLUT_CORE_PROFILE;
	params.windowName = argv[0];
	params.init = init;
	params.displayFunc = display;
	params.reshapeFunc = reshape;
	params.keyboardFunc = Transform::KeyboardFunc;
	app = new GLApplication(&params);

	mesh = new Mesh_Info;
	ReadMeshInfo(dir, filename, mesh);
	mdl = new Model3D;
	mdl->mesh_info = mesh;
	mdl->irender = GetRenderInfo(mesh);
	Vector3 target, position;
	findCameraTargetAndPosition(mesh, &camTarget, &camPos);
	mainCam = new Camera(camPos, camTarget, Vector3::up);
}

void _3DViewerAppRun()
{
	app->Run();
}

void _3DViewerAppShutdown()
{
	FreeMeshInfo(mesh);
	if (mesh)
		delete mesh;
	if (mdl)
		delete mdl;
	if (mainCam)
		delete mainCam;
	if (app)
		delete app;
}

void findCameraTargetAndPosition(Mesh_Info* m, Vector3* target, Vector3* position)
{
	unsigned i, length = m->verts_info.total;
	Vector3 sum;
	int stride, v = m->verts_info.format / 100;

	float zmax = 0.0f, ymax = 0.0f, xmax = 0.0f;
	float zmin = 0.0f, ymin = 0.0f, xmin = 0.0f;
	float zdist;

	if (v == 3)
		stride = 0;
	else if (v == 6)
		stride = 3;

	float *pf = (float*)m->verts_info.positions;
	for (i = 0; i < length; ++i)
	{
		if (pf[0] > xmax)
			xmax = pf[0];
		else if (pf[0] < xmin)
			xmin = pf[0];

		if (pf[1] > ymax)
			ymax = pf[1];
		else if (pf[1] < ymin)
			ymin = pf[1];

		if (pf[2] > zmax)
			zmax = pf[2];
		else if (pf[2] < zmin)
			zmin = pf[2];
		pf += stride;
	}

	
	zdist  = (abs(ymax - 0.5*(ymax + ymin)) / tanf(60.0f)) - abs(zmax - 0.5*(zmax + zmin));
	(*target)[0] = 0.5f * (xmax + xmin);
	(*target)[1] = 0.5f * (ymax + ymin);
	(*target)[2] = 0.5f * (zmax + zmin);

	(*position)[0] = (*target)[0];
	(*position)[1] = (*target)[1];
	(*position)[2] = zmax + abs(zdist) + 20.0f;
}