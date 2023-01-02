#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"
#include <iostream>

/*
====================================================
main
====================================================
*/

int main() {
	Kikurage::Application::Create();
	Kikurage::Application::GetInstance().Run();
	Kikurage::Application::Destroy();

	return 0;
}
