#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

//------------Resource------------
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

namespace Kikurage {
	Application::Application() {
		ResourceManager::Create();

		m_window = new OpenGLWindow(1200, 800, "Kikurage");
		m_eventHandler = new EventHandler();
		m_imguiManager = new GuiManager();
		m_renderer = new Renderer();
		m_ecs = new ECS();
		m_scene3d = new Scene3D();
	}

	Application::~Application() {
		delete m_scene3d;
		delete m_ecs;
		delete m_renderer;
		delete m_imguiManager;
		delete m_eventHandler;
		delete m_window;

		ResourceManager::Destroy();
	}

	void Application::Init() {
		m_renderer->Init();
		m_imguiManager->Init();
		m_ecs->Init();
		m_scene3d->Init();
	}

	void Application::Update(float timeStep) {
		m_scene3d->Update(timeStep);
		if (m_window->IsKeyPressed(GLFW_KEY_E)) {
			this->isEditorEnable = !this->isEditorEnable;
		}
	}

	void Application::Render() {
		this->m_renderer->Start();
		m_scene3d->Draw();
		this->m_renderer->End();

		if (isEditorEnable) {
			m_imguiManager->StartGUIFrame();
			m_imguiManager->Render();
			m_imguiManager->EndGUIFrame();
		}
		else {
			m_window->Draw();
		}
	}

	void Application::Run() {
		this->Init();

		while (m_window->IsOpen())
		{
			UpdateTime();
			m_window->Clear();
			{
				this->Update(this->deltaTime);
				this->Render();
			}
			m_window->Update();
		}
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
