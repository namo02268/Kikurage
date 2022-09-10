#pragma once

#include "OpenGL/OpenGLWindow.h"

class ImGuiManager {
private:
	OpenGLWindow* m_parentWindow;

public:
	ImGuiManager(OpenGLWindow* window);
	~ImGuiManager();

	void Init();
	void Update();
	void Render();

private:
	void DockSpace();
};