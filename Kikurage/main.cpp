#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Scene.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "EventHandler.h"

#include "Renderer.h"
#include "CameraSystem.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "CameraComponent.h"

int main() {
	Window window(800, 600, "Kikurage");

	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_shared<EventHandler>();
	Scene scene(std::move(entityManager), eventHandler);

	//-----------------------------------resource-----------------------------------//
	ResourceManager::LoadShaderFromFile("resources/shaders/Phong.vert", "resources/shaders/Phong.frag", nullptr, "Phong");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");


	//-----------------------------add systems to scene-----------------------------//
	// camera system
	auto cameraSystem = std::make_unique<CameraSystem>(&window, ResourceManager::GetShader("Phong"));
	scene.addSystem(std::move(cameraSystem));
	// renderer
	auto renderer = std::make_unique<Renderer>(ResourceManager::GetShader("Phong"));
	scene.addSystem(std::move(renderer));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = scene.createEntity();
	scene.addComponent<TransformComponent>(cameraEntity, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<CameraComponent>(cameraEntity);

	// suzanne
	auto suzanne = scene.createEntity();
	scene.addComponent<TransformComponent>(suzanne);
	scene.addComponent<MeshComponent>(suzanne, ResourceManager::GetMesh("suzanne"));
	scene.addComponent<MaterialComponent>(suzanne);

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