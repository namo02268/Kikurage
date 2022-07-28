#pragma once

#include "OpenGL/OpenGLWindow.h"

#include "Kikurage/GUI/ImGuiLayer.h"
#include "Kikurage/GUI/SceneWindow.h"
#include "Kikurage/GUI/Editor.h"
#include "Kikurage/Core/EventHandler.h"

#include "Kikurage/Scene/Scene3D.h"

class Application {
private:
	static Application* s_Instance;

	OpenGLWindow* m_window;

	ImGuiLayer* m_guiLayer;
	SceneWindow* m_sceneWindow;
	Scene3D* m_scene3d;
	SceneEditor* m_sceneEditor;

	EventHandler* m_eventHandler;

public:
	Application();
	virtual ~Application();

	static Application& GetInstance() { return *s_Instance; }
	EventHandler& GetEventHandler() { return *this->m_eventHandler; }

	void Run();
};


