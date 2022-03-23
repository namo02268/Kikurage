//------------OpenGL------------
#include "OpenGL/OpenGLWindow.h"

//------------GUI------------
#include "Kikurage/GUI/ImGuiLayer.h"
#include "Kikurage/GUI/SceneWindow.h"
#include "Kikurage/GUI/Editor.h"

//------------Resource------------
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

//------------Scene------------
#include "Kikurage/Scene/Scene3D.h"

int main() {
	OpenGLWindow window(1200, 800, "Kikurage");

	ImGuiLayer guiLayer(&window);
	SceneWindow sceneWindow(800, 600, "Scene");

//	Scene3D scene3d(&sceneWindow);
	Scene3D scene3d(&sceneWindow);
	SceneEditor sceneEditor(scene3d.GetScene());

	// timing
	float deltaTime = 0.0f;
	float lastFrame = window.GetTime();

	//--------------------------------------render loop--------------------------------------//
	while (!window.Closed())
	{
		float currentFrame = window.GetTime();
		deltaTime = currentFrame - lastFrame;
		if (deltaTime >= 1.0f / 120.0f) {
			lastFrame = currentFrame;

			window.Clear();
			{
				guiLayer.begin();

				{
					scene3d.Update(deltaTime);
					scene3d.Draw();

				}
				
				sceneEditor.draw();
				guiLayer.end();
			}
			window.Update();
		}
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}
