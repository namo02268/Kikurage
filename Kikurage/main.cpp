#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Scene.h"
#include "Shader.h"
#include "ResourceManager.h"

#include "EventHandler.h"

#include "SpriteRenderer.h"
#include "CameraSystem.h"
#include "MotionSystem.h"
#include "Player.h"
#include "ColliderSystem.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"
#include "MotionComponent.h"
#include "PlayerComponent.h"
#include "ColliderComponent.h"

int main() {
	Window window(800, 600, "Kikurage");

	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_shared<EventHandler>();
	Scene scene(std::move(entityManager), eventHandler);

	//-----------------------------------resource-----------------------------------//
	ResourceManager::LoadShaderFromFile("resources/shaders/sprite.vert", 
										"resources/shaders/sprite.frag", nullptr, "sprite");

	//-----------------------------add systems to scene-----------------------------//
	// camera
	auto cameraSystem = std::make_unique<CameraSystem>(ResourceManager::GetShader("sprite"), &window);
	scene.addSystem(std::move(cameraSystem));
	// Input
	auto inputSystem = std::make_unique<Player>(&window);
	scene.addSystem(std::move(inputSystem));
	// motion
	auto motionSystem = std::make_unique<MotionSystem>();
	scene.addSystem(std::move(motionSystem));
	// collider
	auto colliderSystem = std::make_unique<ColliderSystem>();
	scene.addSystem(std::move(colliderSystem));
	// sprite
	auto spriteRenderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
	scene.addSystem(std::move(spriteRenderer));

	//---------------------------------add entities---------------------------------//
	// camera
	auto camera = scene.createEntity();
	scene.addComponent<TransformComponent>(camera, glm::vec2(0.0f), glm::vec2(1.0f), 0.0f);
	scene.addComponent<CameraComponent>(camera);

	// enemy
	auto enemy = scene.createEntity();
	scene.addComponent<TransformComponent>(enemy, glm::vec2(0.0f), glm::vec2(1.0f), 0.0f);
	scene.addComponent<SpriteComponent>(enemy,
		ResourceManager::LoadTexture("resources/textures/block.png", false, "block"),
		glm::vec3(1.0f, 0.0f, 0.0f), 1, 1);
	scene.addComponent<ColliderComponent>(enemy, false);

	// player
	auto player = scene.createEntity();
	scene.addComponent<TransformComponent>(player, glm::vec2(3.0f, 3.0f), glm::vec2(1.0f), 0.0f);
	scene.addComponent<SpriteComponent>(player, 
		ResourceManager::LoadTexture("resources/textures/chara/pipo-charachip001.png", true, "Chara"), 
		glm::vec3(1.0f, 1.0f, 1.0f), 4, 3);
	scene.addComponent<MotionComponent>(player);
	scene.addComponent<PlayerComponent>(player);
	scene.addComponent<ColliderComponent>(player, true);

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

