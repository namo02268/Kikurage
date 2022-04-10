#include "Kikurage/Core/Application.h"
#include <iostream>

/*
====================================================
main
====================================================
*/

int main() {
	new Application();

	Application::GetInstance().Run();

	return 0;
}
