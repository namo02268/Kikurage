#include "Kikurage/Core/Application/Application.h"
#include "Editor/Editor.h"
#include "Utils/Factory.h"

int main() {
	/*
	Kikurage::Application::Create();
	Kikurage::Application::GetInstance().Run();
	Kikurage::Application::Destroy();
	*/
	Kikurage::Application::Create();
	Kikurage::Editor editor(&Kikurage::Application::GetInstance());
	editor.Run();
	Kikurage::Application::Destroy();

	/*
	Resource<int> test;
	std::cout << test.id << std::endl;
	*/
	return 0;
}
