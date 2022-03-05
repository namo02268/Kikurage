#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Scene.h"
#include "Shader.h"
#include "ResourceManager.h"

#include "EventHandler.h"

int main() {
	Window window(800, 600, "Kikurage");

	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_shared<EventHandler>();
	Scene scene(std::move(entityManager), eventHandler);

	//-----------------------------------resource-----------------------------------//

	//-----------------------------add systems to scene-----------------------------//

	//---------------------------------add entities---------------------------------//

	// init
	scene.init();

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	//--------------------------------------render loop--------------------------------------//
	while (!window.Closed())
	{
		float currentFrame = window.GetTime();
		deltaTime = currentFrame - lastFrame;
		if (deltaTime >= 1.0f / 60.0f) {
			lastFrame = currentFrame;


			window.Clear();

			scene.update(deltaTime);
			scene.draw();

			window.Update();

			if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
				std::cout << "Pressed!" << std::endl;
			}
		}
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}