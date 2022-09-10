#pragma once

#include "OpenGL/OpenGLWindow.h"

#include "Kikurage/GUI/ImGuiManager.h"
#include "Kikurage/GUI/SceneEditor.h"
#include "Kikurage/Events/EventHandler.h"
#include "Kikurage/Core/Renderer/Renderer.h"

#include "Kikurage/Scene/Scene3D.h"

class Application {
private:
	static inline Application* s_Instance = nullptr;

	OpenGLWindow* m_window;
	Renderer* m_renderer;
	ImGuiManager* m_imguiManager;
	SceneEditor* m_sceneEditor;
	Scene3D* m_scene3d;
	EventHandler* m_eventHandler;

	bool isEditorEnable = true;

	// time
	float timeScale = 1.0f;
	float deltaTime = 0.0f;
	std::size_t FPS = 0;

public:
	Application();
	virtual ~Application();

	static Application& GetInstance() { return *s_Instance; }

	void Run();

	void Init();
	void Update(float timeStep);
	void Render();

	void UpdateTime();

	float GetDeltaTime() const { return this->deltaTime; }
	std::size_t GetFPS() const { return this->FPS; }
	EventHandler& GetEventHandler() const { return *this->m_eventHandler; }
	Window* GetWindow() const { return this->m_window; }
	Renderer* GetRenderer() const { return this->m_renderer; }
	Scene* GetScene() const { return this->m_scene3d->GetScene(); }
};


