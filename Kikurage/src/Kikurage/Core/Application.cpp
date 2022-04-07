#include "Application.h"

//------------Resource------------
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

Application* Application::s_Instance = nullptr;

Application::Application() {
	s_Instance = this;

	m_window = new OpenGLWindow(1200, 800, "Kikurage");
	m_guiLayer = new ImGuiLayer(m_window);
	m_sceneWindow = new SceneWindow(800, 600, "Scene");
	m_scene3d = new Scene3D(m_sceneWindow);
	m_sceneEditor = new SceneEditor(m_scene3d->GetScene());
}

Application::~Application() {
	ResourceManager::Clear();

	delete m_window;
	delete m_guiLayer;
	delete m_sceneWindow;
	delete m_scene3d;
	delete m_sceneEditor;
}

void Application::Run() {
	// timing
	float deltaTime = 0.0f;
	float lastFrame = m_window->GetTime();

	//--------------------------------------render loop--------------------------------------//
	while (!m_window->Closed())
	{
		float currentFrame = m_window->GetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_window->Clear();
		{
			m_guiLayer->begin();
			{
				m_scene3d->Update(deltaTime);
				m_scene3d->Draw();
			}
			m_sceneEditor->draw();
			m_guiLayer->end();
		}
		m_window->Update();
	}

}