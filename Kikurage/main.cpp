#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Window.h"
#include "Scene.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "EventHandler.h"

#include "Renderer.h"
#include "CameraSystem.h"
#include "IBL.h"
#include "GUI.h"
#include "MotionSystem.h"

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "MotionComponent.h"
#include "GUIComponent.h"

int main() {
	Window window(800, 600, "Kikurage");

	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_unique<EventHandler>();
	Scene scene(std::move(entityManager), std::move(eventHandler));

	//-----------------------------------Resources-----------------------------------//
	stbi_set_flip_vertically_on_load(true);

	ResourceManager::LoadShaderFromFile("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
	ResourceManager::LoadShaderFromFile("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");
	ResourceManager::LoadMeshFromFile("resources/objects/sphere/sphere.obj", "sphere");

	//-----------------------------add systems to scene-----------------------------//
	// motion system
	auto motionSystem = std::make_unique<MotionSystem>();
	scene.addSystem(std::move(motionSystem));

	// camera system
	auto cameraSystem = std::make_unique<CameraSystem>(&window);
	cameraSystem->addShader(ResourceManager::GetShader("PBR"));
	cameraSystem->addShader(ResourceManager::GetShader("backgroundShader"));
	scene.addSystem(std::move(cameraSystem));
	// renderer
	auto renderer = std::make_unique<Renderer>(ResourceManager::GetShader("PBR"));
	scene.addSystem(std::move(renderer));
	// IBL
	auto ibl = std::make_unique<IBL>(ResourceManager::GetShader("PBR"), ResourceManager::GetShader("backgroundShader"));
	scene.addSystem(std::move(ibl));
	// GUI
	auto gui = std::make_unique<GUI>(&window);
	scene.addSystem(std::move(gui));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = scene.createEntity();
	scene.addComponent<TransformComponent>(cameraEntity, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<CameraComponent>(cameraEntity);

	/*
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			auto sphere = scene.createEntity();
			scene.addComponent<TransformComponent>(sphere, glm::vec3(4.0f * i, 0.0f, 4.0f * j), glm::vec3(1.0f), glm::vec3(0.0f));
			scene.addComponent<MotionComponent>(sphere, glm::vec3(0.0f), 
														glm::vec3(0.0f), 
														glm::vec3((float)rand() / RAND_MAX * 50, (float)rand() / RAND_MAX * 50, (float)rand() / RAND_MAX * 50),
														glm::vec3(0.0f), 
														glm::vec3(0.0f), 
														glm::vec3(0.0f));
			scene.addComponent<MeshComponent>(sphere, ResourceManager::GetMesh("suzanne"));
			scene.addComponent<MaterialComponent>(sphere, glm::vec3((float)rand() / RAND_MAX, rand() % 2, (float)rand() / RAND_MAX), (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
		} 
	}
	*/

	// suzanne
	auto suzanne = scene.createEntity();
	scene.addComponent<TransformComponent>(suzanne);
	scene.addComponent<MeshComponent>(suzanne, ResourceManager::GetMesh("suzanne"));
	scene.addComponent<MaterialComponent>(suzanne);
	scene.addComponent<MotionComponent>(suzanne);
	scene.addComponent<GUIComponent>(suzanne);

	auto sphere1 = scene.createEntity();
	scene.addComponent<TransformComponent>(sphere1, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere1, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere1);
	scene.addComponent<GUIComponent>(sphere1);

	auto sphere2 = scene.createEntity();
	scene.addComponent<TransformComponent>(sphere2, glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere2, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere2);
	scene.addComponent<GUIComponent>(sphere2);

	auto sphere3 = scene.createEntity();
	scene.addComponent<TransformComponent>(sphere3, glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere3, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere3);
	scene.addComponent<GUIComponent>(sphere3);

	// init
	scene.init();

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// then before rendering, configure the viewport to the original framebuffer's screen dimensions
	int scrWidth, scrHeight;
	glfwGetFramebufferSize(window.GetWindow(), &scrWidth, &scrHeight);
	glViewport(0, 0, scrWidth, scrHeight);

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
		}
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}
