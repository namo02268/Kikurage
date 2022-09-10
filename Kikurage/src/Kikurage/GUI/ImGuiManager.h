#pragma once

#include <iostream>

#include "OpenGL/OpenGLWindow.h"
#include "ComponentEditor.h"

class ImGuiManager {
private:
	OpenGLWindow* m_parentWindow;
	std::unique_ptr<ComponentEditor> m_componentEditor = std::make_unique<ComponentEditor>();

public:
	ImGuiManager(OpenGLWindow* window);
	~ImGuiManager();

	void Init();
	void Update(float dt);
	void Render();

private:
	void BeginDockSpace();
};