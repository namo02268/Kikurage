#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"
#include <iostream>

/*
====================================================
main
====================================================
*/

int main() {
	Application::Create();
	Application::GetInstance().Run();
	Application::Destroy();

	return 0;
}
