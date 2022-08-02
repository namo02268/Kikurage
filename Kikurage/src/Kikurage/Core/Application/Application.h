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

	float timeScale = 1.0f;
	float deltaTime = 0.0f;
	std::size_t FPS = 0;

public:
	Application();
	virtual ~Application();

	static Application& GetInstance() { return *s_Instance; }
	EventHandler& GetEventHandler() { return *this->m_eventHandler; }
	Window* GetWindow() { return this->m_window; }

	void Run();

	void UpdateTime();
	float GetDeltaTime() const { return this->deltaTime; }
	std::size_t GetFPS() const { return this->FPS; }
};


