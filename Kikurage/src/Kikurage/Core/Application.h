#pragma once

#include "OpenGL/OpenGLWindow.h"
#include "Kikurage/GUI/ImGuiLayer.h"
#include "Kikurage/GUI/SceneWindow.h"
#include "Kikurage/GUI/Editor.h"
#include "Kikurage/Events/EventHandler.h"
#include "Kikurage/Scene/Scene3D.h"

class Application {
private:
	static inline Application* s_Instance = nullptr;

	OpenGLWindow* m_window;
	ImGuiLayer* m_guiLayer;
	SceneWindow* m_sceneWindow;
	Scene3D* m_scene3d;
	SceneEditor* m_sceneEditor;
	EventHandler* m_eventHandler;

	bool m_isRunning = false;

public:
	Application();
	virtual ~Application();

	void Run();

	static Application& GetInstance() { return *s_Instance; }
	EventHandler& GetEventHandler() const { return *this->m_eventHandler; }

	bool IsRunning() const { return m_isRunning; }
};


