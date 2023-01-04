#pragma once

#include "OpenGL/OpenGLWindow.h"

#include "Kikurage/GUI/GuiManager.h"
#include "Kikurage/Events/EventHandler.h"
#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Scene/Scene3D.h"

#include "Utils/Singleton.h"

namespace Kikurage {
	class Application : public Singleton<Application> {
	private:
		OpenGLWindow* m_window;
		Renderer* m_renderer;
		GuiManager* m_imguiManager;
		ECS* m_ecs;
		Scene3D* m_scene3d;
		EventHandler* m_eventHandler;

		// time
		float timeScale = 1.0f;
		float deltaTime = 0.0f;
		std::size_t FPS = 0;

	public:
		bool isEditorEnable = true;

	protected:
		Application();
		virtual ~Application();

	public:
		friend class Singleton<Application>;

		void Run();
		void Init();
		void Update(float timeStep);
		void Render();

		void UpdateTime();

		const float GetDeltaTime() const { return this->deltaTime; }
		const std::size_t GetFPS() const { return this->FPS; }

		OpenGLWindow* GetWindow() const { return this->m_window; }
		Renderer* GetRenderer() const { return this->m_renderer; }
		GuiManager* GetGUIManager() const { return this->m_imguiManager; }
		ECS* GetECS() const { return this->m_ecs; }
		EventHandler& GetEventHandler() const { return *this->m_eventHandler; }
	};
}
