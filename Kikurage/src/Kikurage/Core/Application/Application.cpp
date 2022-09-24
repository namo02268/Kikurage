#include "Kikurage/Core/Application/Application.h"

//------------Resource------------
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

/*
====================================================
Application::Application
====================================================
*/
Application::Application() {
	m_window = new OpenGLWindow(1200, 800, "Kikurage");
	m_eventHandler = new EventHandler();
	m_imguiManager = new ImGuiManager(m_window);
	m_renderer = new Renderer();
	m_scene3d = new Scene3D();
}

/*
====================================================
Application::~Application
====================================================
*/
Application::~Application() {
	ResourceManager::Clear();

	delete m_window;
	delete m_renderer;
	delete m_imguiManager;
	delete m_scene3d;
	delete m_eventHandler;
}

void Application::Init() {
	m_imguiManager->Init();
	m_renderer->Init();
}

void Application::Update(float timeStep) {
	m_imguiManager->Update(timeStep);
	m_scene3d->Update(timeStep);
}

void Application::Render() {
	this->m_renderer->Start();
	m_scene3d->Draw();
	this->m_renderer->End();

	m_imguiManager->Render();
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
		std::cout << FPS << std::endl;
		lastSecond = currentFrame;
		frameCount = 0;
	}

	this->deltaTime = this->timeScale * (currentFrame - lastFrame);
	// TODO : ADD this->totalTime += this->deltaTime;
	lastFrame = currentFrame;
}