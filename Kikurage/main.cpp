#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"
#include <iostream>

int main() {
	//new Application();
	//Application::GetInstance().Run();

	MeshLoader::LoadFromFile("resources/objects/suzanne/suzanne.obj");

	MeshLoader::LoadFromFile("resources/objects/testMesh/testMesh2.obj");

	MeshLoader::LoadFromFile("resources/objects/sponza/sponza.obj");

	return 0;
}
