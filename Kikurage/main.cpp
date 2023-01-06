#include "Kikurage/Core/Application/Application.h"

int main() {
	Kikurage::Application::Create();
	Kikurage::Application::GetInstance().Run();
	Kikurage::Application::Destroy();

	return 0;
}
