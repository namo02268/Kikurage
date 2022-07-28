#include "Kikurage/Core/Application/Application.h"
#include <iostream>

int main() {
	new Application();

	Application::GetInstance().Run();

	return 0;
}
