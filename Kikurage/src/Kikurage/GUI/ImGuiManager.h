#pragma once

#include <iostream>

#include "OpenGL/OpenGLWindow.h"
#include "Kikurage/GUI/ComponentEditor.h"
#include "Kikurage/GUI/ViewportEditor.h"

class ImGuiManager {
private:
	OpenGLWindow* m_parentWindow;
	std::unique_ptr<ComponentEditor> m_componentEditor = std::make_unique<ComponentEditor>();
	std::unique_ptr<ViewportEditor> m_sceneEditor = std::make_unique<ViewportEditor>(800, 600, "Scene");

public:
	ImGuiManager(OpenGLWindow* window);
	~ImGuiManager();

	void Init();
	void Update(float dt);
	void Render();

private:
	void BeginDockSpace();
};