#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/Mesh/MeshLoader.h"
#include <iostream>

int main() {
	new Application();
	Application::GetInstance().Run();

	return 0;
}
