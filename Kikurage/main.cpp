#include "Kikurage/Core/Application.h"
#include <iostream>

int main() {
	new Application();
	std::cout << &Application::GetInstance() << std::endl;

	Application::GetInstance().Run();

	return 0;
}
