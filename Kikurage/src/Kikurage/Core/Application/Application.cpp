#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	Application::Application() {
		m_eventHandler = new EventHandler();
		m_ecs = new ECS();
		m_window = new OpenGLWindow(1200, 800, "Kikurage");
		m_renderer = new Renderer();
		m_scene3d = new Scene3D();
	}

	Application::~Application() {}

	void Application::Run() {
		this->Init();

		while (this->ShouldClose())
		{
			this->Update();
			this->Render();
			this->PollEvents();
		}

		this->Shutdown();
	}

	void Application::Init() {
		std::cout << "Hello Kikurage!" << "\n";
		std::cout << "Initialize ECS..." << "\n";
		m_ecs->Init();
		std::cout << "Initialize Renderer..." << "\n";
		m_renderer->Init();
		std::cout << "Loading the Scene..." << "\n";
		m_scene3d->Init();
	}

	void Application::Shutdown() {
		std::cout << "Shutdown Application..." << std::endl;
		delete m_scene3d;
		delete m_renderer;
		delete m_window;
		delete m_ecs;
		delete m_eventHandler;
	}

	void Application::Update() {
		this->UpdateTime();
		m_scene3d->Update(this->deltaTime);
	}

	void Application::Render() {
		this->m_renderer->Start();
		m_scene3d->Draw();
		this->m_renderer->End();
	}

	void Application::PollEvents() {
		this->m_window->PollEvents();
	}

	void Application::UpdateTime() {
		static float lastFrame = m_window->GetTime();
		static float lastSecond = m_window->GetTime();
		static std::size_t frameCount = 0;

		float currentFrame = m_window->GetTime();

		// TODO : ADD if(paused)

		frameCount++;
		if (lastFrame - lastSecond >= 1.0f) {
			this->FPS = frameCount;
			lastSecond = currentFrame;
			frameCount = 0;
		}

		this->deltaTime = this->timeScale * (currentFrame - lastFrame);
		// TODO : ADD this->totalTime += this->deltaTime;
		lastFrame = currentFrame;
	}
}
