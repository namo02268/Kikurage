#include "Kikurage/Core/Application.h"
#include <iostream>

int main() {
	new Application();
	Application::GetInstance().Run();

	return 0;
}
