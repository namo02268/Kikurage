#pragma once

#include "Kikurage/Events/EventHandler.h"
#include "Kikurage/Core/ECS/ECS.h"
#include "OpenGL/OpenGLWindow.h"
#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Scene/Scene3D.h"

#include "Utils/Singleton.h"

namespace Kikurage {
	class Application : public Singleton<Application> {
	private:
		EventHandler* m_eventHandler;
		KikurageECS* m_ecs;
		OpenGLWindow* m_window;
		Renderer* m_renderer;
		Scene3D* m_scene3d;

		// time
		float timeScale = 1.0f;
		float deltaTime = 0.0f;
		std::size_t FPS = 0;

	protected:
		Application();
		virtual ~Application();

	public:
		friend class Singleton<Application>;

		void Run();

		void Init();
		void Shutdown();
		void Update();
		void Render();
		void PollEvents();

		void UpdateTime();

		bool ShouldClose() { return this->m_window->IsOpen(); }

		const float GetDeltaTime() const { return this->deltaTime; }
		const std::size_t GetFPS() const { return this->FPS; }

		EventHandler& GetEventHandler() const { return *this->m_eventHandler; }
		KikurageECS* GetECS() const { return this->m_ecs; }
		OpenGLWindow* GetWindow() const { return this->m_window; }
		Renderer* GetRenderer() const { return this->m_renderer; }
	};
}
