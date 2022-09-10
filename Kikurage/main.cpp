#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"
#include <iostream>

/*
====================================================
main
====================================================
*/

int main() {
	new Application();

	Application::GetInstance().Run();

	delete &Application::GetInstance();

	return 0;
}
