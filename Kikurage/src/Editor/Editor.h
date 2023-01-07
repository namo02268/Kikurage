#pragma once

#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	class Editor {
	private:
		Application* app;

	public:
		Editor(Application* app) : app(app) {}
		~Editor() = default;

		void Run();

	private:
		void InitImGUI();
		void ShutdownImGUI();

		void StartGUIFrame();
		void Render();
		void EndGUIFrame();
	};
}
