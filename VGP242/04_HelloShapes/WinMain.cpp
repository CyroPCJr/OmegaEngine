#include <OmegaEngine/Inc/Omega.h>

#include "Shapes.h"
#include "Polygons.h"

/*
	 Add 04_HelloShapes project
	 Copy code from 03_HelloTriangle
	 Update to use DoSomething fx shaders
	 Update Vertex to have Color as well
	 Make sure inputLayout is initializes with correct description
	 Create multiple meshes and vertex buffers
	 - Draw a heart
	 - Draw a triforce (Zelda)
	 - Draw something with more than 5 triangles
	 Use input check so you can change between them
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<HeartShape>("HeartShape");
	Omega::MainApp().AddState<Triforce>("Triforce");
	Omega::MainApp().AddState<RandomPolygon>("RandomPolygon");
	Omega::MainApp().Run({"Hello Shapes Project", 1280,720});
	return 0;
}