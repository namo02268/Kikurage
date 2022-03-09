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

#include "CameraComponent.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

int main() {
	Window window(800, 600, "Kikurage");

	//-------------------------------initialize scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_shared<EventHandler>();
	Scene scene(std::move(entityManager), eventHandler);

	//-----------------------------------Resources-----------------------------------//
	stbi_set_flip_vertically_on_load(true);

	ResourceManager::LoadShaderFromFile("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
	ResourceManager::LoadShaderFromFile("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");
	ResourceManager::LoadMeshFromFile("resources/objects/sphere/sphere.obj", "sphere");

	//-----------------------------add systems to scene-----------------------------//
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

	// suzanne
	auto suzanne = scene.createEntity();
	scene.addComponent<TransformComponent>(suzanne);
	scene.addComponent<MeshComponent>(suzanne, ResourceManager::GetMesh("suzanne"));
	scene.addComponent<MaterialComponent>(suzanne);

	auto sphere1 = scene.createEntity();
	scene.addComponent<TransformComponent>(sphere1, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere1, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere1);

	auto sphere2 = scene.createEntity();
	scene.addComponent<TransformComponent>(sphere2, glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere2, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere2);

	auto sphere3 = scene.createEntity();
	scene.addComponent<TransformComponent>(sphere3, glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	scene.addComponent<MeshComponent>(sphere3, ResourceManager::GetMesh("sphere"));
	scene.addComponent<MaterialComponent>(sphere3);

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

			// UI
			ImGui::NewFrame();
			ImGui::SetNextWindowPos(ImVec2(window.GetWidth() - 300, 0.0));
			ImGui::SetNextWindowSize(ImVec2(300, window.GetHeight()));
			bool open;

			ImGui::Begin("Model", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			ImGui::PushID(suzanne.GetID());
			if (ImGui::CollapsingHeader("Suzanne")) {
				if (ImGui::TreeNode("Transform")) {
					ImGui::DragFloat3("Position", &scene.getComponent<TransformComponent>(suzanne).position.x, 0.01f);
					ImGui::DragFloat3("Scale", &scene.getComponent<TransformComponent>(suzanne).scale.x, 0.01f);
					ImGui::DragFloat3("Rotation", &scene.getComponent<TransformComponent>(suzanne).rotation.x, 1.0f);
					ImGui::TreePop();
				}
				ImGui::Separator();
				if (ImGui::TreeNode("Material")) {
					ImGui::ColorEdit3("Albedo", &scene.getComponent<MaterialComponent>(suzanne).albedo.x);
					ImGui::SliderFloat("Metallic", &scene.getComponent<MaterialComponent>(suzanne).metallic, 0.0f, 1.0f);
					ImGui::SliderFloat("Roughness", &scene.getComponent<MaterialComponent>(suzanne).roughness, 0.0f, 1.0f);
					ImGui::SliderFloat("ao", &scene.getComponent<MaterialComponent>(suzanne).ao, 0.0f, 1.0f);
					ImGui::TreePop();
				}
			}
			ImGui::PopID();

			ImGui::PushID(sphere1.GetID());
			if (ImGui::CollapsingHeader("sphere1")) {
				if (ImGui::TreeNode("Transform")) {
					ImGui::DragFloat3("Position", &scene.getComponent<TransformComponent>(sphere1).position.x, 0.01f);
					ImGui::DragFloat3("Scale", &scene.getComponent<TransformComponent>(sphere1).scale.x, 0.01f);
					ImGui::DragFloat3("Rotation", &scene.getComponent<TransformComponent>(sphere1).rotation.x, 1.0f);
					ImGui::TreePop();
				}
				ImGui::Separator();
				if (ImGui::TreeNode("Material")) {
					ImGui::ColorEdit3("Albedo", &scene.getComponent<MaterialComponent>(sphere1).albedo.x);
					ImGui::SliderFloat("Metallic", &scene.getComponent<MaterialComponent>(sphere1).metallic, 0.0f, 1.0f);
					ImGui::SliderFloat("Roughness", &scene.getComponent<MaterialComponent>(sphere1).roughness, 0.0f, 1.0f);
					ImGui::SliderFloat("ao", &scene.getComponent<MaterialComponent>(sphere1).ao, 0.0f, 1.0f);
					ImGui::TreePop();
				}
			}
			ImGui::PopID();

			ImGui::PushID(sphere2.GetID());
			if (ImGui::CollapsingHeader("sphere2")) {
				if (ImGui::TreeNode("Transform")) {
					ImGui::DragFloat3("Position", &scene.getComponent<TransformComponent>(sphere2).position.x, 0.01f);
					ImGui::DragFloat3("Scale", &scene.getComponent<TransformComponent>(sphere2).scale.x, 0.01f);
					ImGui::DragFloat3("Rotation", &scene.getComponent<TransformComponent>(sphere2).rotation.x, 1.0f);
					ImGui::TreePop();
				}
				ImGui::Separator();
				if (ImGui::TreeNode("Material")) {
					ImGui::ColorEdit3("Albedo", &scene.getComponent<MaterialComponent>(sphere2).albedo.x);
					ImGui::SliderFloat("Metallic", &scene.getComponent<MaterialComponent>(sphere2).metallic, 0.0f, 1.0f);
					ImGui::SliderFloat("Roughness", &scene.getComponent<MaterialComponent>(sphere2).roughness, 0.0f, 1.0f);
					ImGui::SliderFloat("ao", &scene.getComponent<MaterialComponent>(sphere2).ao, 0.0f, 1.0f);
					ImGui::TreePop();
				}
			}
			ImGui::PopID();

			ImGui::PushID(sphere3.GetID());
			if (ImGui::CollapsingHeader("sphere3")) {
				if (ImGui::TreeNode("Transform")) {
					ImGui::DragFloat3("Position", &scene.getComponent<TransformComponent>(sphere3).position.x, 0.01f);
					ImGui::DragFloat3("Scale", &scene.getComponent<TransformComponent>(sphere3).scale.x, 0.01f);
					ImGui::DragFloat3("Rotation", &scene.getComponent<TransformComponent>(sphere3).rotation.x, 1.0f);
					ImGui::TreePop();
				}
				ImGui::Separator();
				if (ImGui::TreeNode("Material")) {
					ImGui::ColorEdit3("Albedo", &scene.getComponent<MaterialComponent>(sphere3).albedo.x);
					ImGui::SliderFloat("Metallic", &scene.getComponent<MaterialComponent>(sphere3).metallic, 0.0f, 1.0f);
					ImGui::SliderFloat("Roughness", &scene.getComponent<MaterialComponent>(sphere3).roughness, 0.0f, 1.0f);
					ImGui::SliderFloat("ao", &scene.getComponent<MaterialComponent>(sphere3).ao, 0.0f, 1.0f);
					ImGui::TreePop();
				}
			}
			ImGui::PopID();

			ImGui::End();


			scene.draw();

			window.Update();
		}
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	return 0;
}
