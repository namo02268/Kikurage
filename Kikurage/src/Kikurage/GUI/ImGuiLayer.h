#pragma once

#include "OpenGL/OpenGLWindow.h"

class ImGuiLayer {
private:
	OpenGLWindow* m_parentWindow;

public:
	ImGuiLayer(OpenGLWindow* window);
	~ImGuiLayer();

	void init();
	void begin();
	void end();

private:
	void DockSpace();
};