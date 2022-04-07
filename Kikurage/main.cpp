#include "Kikurage/Core/Application.h"

int main() {
	new Application();

	Application::GetInstance().Run();

	return 0;
}
