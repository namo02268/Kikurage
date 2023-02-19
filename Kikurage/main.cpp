#include "Kikurage/Core/Application/Application.h"
#include "Editor/Editor.h"

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

	return 0;
}
