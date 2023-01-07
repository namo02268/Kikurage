#include "Kikurage/Core/Application/Application.h"
#include "Editor/Editor.h"

int main() {
	Kikurage::Application::Create();
	Kikurage::Editor editor(&Kikurage::Application::GetInstance());
	editor.Run();
	Kikurage::Application::Destroy();

	return 0;
}
