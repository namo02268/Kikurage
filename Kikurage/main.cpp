#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

//------------imgui------------
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//------------OpenGL------------
#include "OpenGL/OpenGLWindow.h"

//------------ECS------------
#include "ECS/Scene.h"
#include "ECS/EventHandler.h"

//------------Resource------------
#include "Resources/Shader/Shader.h"
#include "Resources/ResourceManager/ResourceManager.h"

//------------imgui------------
#include "GUI/ImGuiLayer.h"
#include "GUI/SceneWindow.h"
#include "GUI/Editor.h"

//------------Systems------------
#include "Systems/MeshRenderer/MeshRenderer.h"
#include "Systems/Camera/CameraSystem.h"
#include "Systems/IBL/IBL.h"
#include "Systems/Physics/Physics.h"
#include "Systems/Collision/CollisionSystem.h"
#include "Systems/Collision/SphereCollider.h"
#include "Systems/Collision/PlaneCollider.h"

//------------Components------------
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/CollisionComponent.h"

int main() {
	OpenGLWindow window(800, 600, "Kikurage");
	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_unique<EventHandler>();
	Scene scene(std::move(entityManager), std::move(eventHandler));

	//-------------------------------initialize GUIs-------------------------------//
	ImGuiLayer guiLayer(&window);
	SceneWindow sceneWindow(800, 600, "Kikurage");
	Editor editor(&scene);

	//-----------------------------------Resources-----------------------------------//
	stbi_set_flip_vertically_on_load(true);

	ResourceManager::LoadShaderFromFile("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
	ResourceManager::LoadShaderFromFile("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");
	ResourceManager::LoadMeshFromFile("resources/objects/sphere/sphere.obj", "sphere");
	ResourceManager::LoadMeshFromFile("resources/objects/plane/plane.obj", "plane");

	//-----------------------------add systems to scene-----------------------------//
	// camera system
	auto cameraSystem = std::make_unique<CameraSystem>(&sceneWindow);
	cameraSystem->addShader(ResourceManager::GetShader("PBR"));
	cameraSystem->addShader(ResourceManager::GetShader("backgroundShader"));
	scene.addSystem(std::move(cameraSystem));
	// meshRenderer
	auto meshRenderer = std::make_unique<MeshRenderer>(ResourceManager::GetShader("PBR"));
	scene.addSystem(std::move(meshRenderer));
	// IBL
	auto ibl = std::make_unique<IBL>(ResourceManager::GetShader("PBR"), ResourceManager::GetShader("backgroundShader"));
	scene.addSystem(std::move(ibl));
	// Physics
	auto physics = std::make_unique<Physics>();
	scene.addSystem(std::move(physics));
	// Collision 
	auto collisionSystem = std::make_unique<CollisionSystem>();
	scene.addSystem(std::move(collisionSystem));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = scene.createEntity();
	scene.addComponent<TransformComponent>(cameraEntity, glm::vec3(20.0f, 5.0f, 20.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<CameraComponent>(cameraEntity);

	// plane
	auto plane = scene.createEntity();
	scene.addComponent<TransformComponent>(plane, glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(3.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(plane, ResourceManager::GetMesh("plane"));
	scene.addComponent<MaterialComponent>(plane);
	scene.addComponent<RigidBodyComponent>(plane, false, true);
	scene.addComponent<CollisionComponent>(plane, new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));

	// init
	scene.init();

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
					window.BindFBO();
					window.Clear();
					if (window.IsKeyPressed(GLFW_KEY_X)) {
						auto sphere1 = scene.createEntity();
						scene.addComponent<TransformComponent>(sphere1, glm::vec3((float)rand() / RAND_MAX * 2, 10.0f, (float)rand() / RAND_MAX * 2), glm::vec3(1.0f), glm::vec3(0.0f));
						scene.addComponent<MeshComponent>(sphere1, ResourceManager::GetMesh("sphere"));
						scene.addComponent<MaterialComponent>(sphere1, glm::vec3((float)rand() / RAND_MAX, rand() % 2, (float)rand() / RAND_MAX), (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
						scene.addComponent<RigidBodyComponent>(sphere1, true, false);
						scene.addComponent<CollisionComponent>(sphere1, new SphereCollider(glm::vec3(0.0f), 1.0f));
					}
					scene.update(deltaTime);
					scene.draw();
					window.UnbindFBO();
				}

				sceneWindow.draw(window.getRenderTexture());
				editor.draw();
				guiLayer.end();
			}
			window.Update();
		}
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}
