#pragma once

#include "OpenGL/OpenGLWindow.h"

#include "Kikurage/GUI/ImGuiLayer.h"
#include "Kikurage/GUI/SceneWindow.h"
#include "Kikurage/GUI/Editor.h"

#include "Kikurage/Scene/Scene3D.h"

class Application {
private:
	static Application* s_Instance;

	OpenGLWindow* m_window;

	ImGuiLayer* m_guiLayer;
	SceneWindow* m_sceneWindow;
	Scene3D* m_scene3d;
	SceneEditor* m_sceneEditor;

public:
	Application();
	virtual ~Application();

	static Application& GetInstance() { return *s_Instance; }

	void Run();
};


