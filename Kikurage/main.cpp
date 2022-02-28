#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Scene.h"
#include "Shader.h"
#include "ResourceManager.h"

#include "SpriteRenderer.h"
#include "CameraSystem.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"



// GLFW Callback
void processInput(GLFWwindow* window);

int main() {
	Window window(800, 600, "Kikurage");

	//--------------------------------------Entity--------------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	Scene scene(std::move(entityManager));

	ResourceManager::LoadShaderFromFile("resources/shaders/sprite.vert", "resources/shaders/sprite.frag", nullptr, "sprite");
	auto cameraSystem = std::make_unique<CameraSystem>(ResourceManager::GetShader("sprite"), &window);
	scene.addSystem(std::move(cameraSystem));
	auto spriteRenderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
	scene.addSystem(std::move(spriteRenderer));

	auto camera = scene.createEntity();
	scene.addComponent<TransformComponent>(camera, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f), 0.0f);
	scene.addComponent<CameraComponent>(camera);

	auto player = scene.createEntity();
	scene.addComponent<TransformComponent>(player, glm::vec2(0.0f), glm::vec2(1.0f), 0.0f);
	scene.addComponent<SpriteComponent>(player, ResourceManager::LoadTexture("resources/textures/block.png", false, "block"));

	scene.init();


	//--------------------------------------render loop--------------------------------------//
	while (!window.Closed())
	{
		window.Clear();

		scene.update();
		scene.draw();

		window.Update();

		if(window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
			std::cout << "Pressed!" << std::endl;
		}

		std::cout << window.GetMouseScroll_Y() << std::endl;

	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}

//--------------------------------------GLFW Callback--------------------------------------//
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
