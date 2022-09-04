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
	s_Instance = this;

	m_window = new OpenGLWindow(1200, 800, "Kikurage");
	m_guiLayer = new ImGuiLayer(m_window);
	m_sceneWindow = new SceneWindow(800, 600, "Scene");

	m_eventHandler = new EventHandler();

	m_scene3d = new Scene3D(m_sceneWindow);
	m_sceneEditor = new SceneEditor(m_scene3d->GetScene());

}

/*
====================================================
Application::~Application
====================================================
*/
Application::~Application() {
	ResourceManager::Clear();

	delete m_window;
	delete m_guiLayer;
	delete m_sceneWindow;
	delete m_scene3d;
	delete m_sceneEditor;
	delete m_eventHandler;
}

/*
====================================================
Application::Run
====================================================
*/
void Application::Run() {
	while (m_window->IsOpen())
	{
		UpdateTime();
		m_window->Clear();
		{
			m_guiLayer->begin();
			{
				m_scene3d->Update(this->deltaTime);
				m_scene3d->Draw();
			}
			m_sceneEditor->draw();
			m_guiLayer->end();
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