#include "Kikurage/Scene/Scene3D.h"
#include "Kikurage/Core/Application/Application.h"

//------------Resource------------
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

//------------Systems------------
#include "Kikurage/Systems/Transform/TransformUpdator.h"
#include "Kikurage/Systems/Renderer/MeshRenderer.h"
#include "Kikurage/Systems/Camera/CameraSystem.h"
#include "Kikurage/Systems/IBL/IBL.h"
#include "Kikurage/Systems/Physics/Physics.h"
#include "Kikurage/Systems/Collision/CollisionSystem.h"
#include "Kikurage/Systems/Collision/SphereCollider.h"
#include "Kikurage/Systems/Collision/PlaneCollider.h"
#include "Kikurage/Systems/AABBCollision/AABBCollision.h"

//------------Components------------
#include "Kikurage/Components/CameraComponent.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Components/RigidBodyComponent.h"
#include "Kikurage/Components/CollisionComponent.h"

Scene3D::Scene3D() {
}

Scene3D::~Scene3D() {
}

void Scene3D::Init() {
	//-----------------------------------Resources-----------------------------------//
	stbi_set_flip_vertically_on_load(true);

	ResourceManager::GetInstance().LoadShaderFromFile("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
	ResourceManager::GetInstance().LoadShaderFromFile("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
	ResourceManager::GetInstance().LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");
	ResourceManager::GetInstance().LoadMeshFromFile("resources/objects/sphere/sphere.obj", "sphere");
	ResourceManager::GetInstance().LoadMeshFromFile("resources/objects/plane/plane.obj", "plane");

	Application::GetInstance().GetRenderer()->AddShader(ResourceManager::GetInstance().GetShader("PBR"));
	Application::GetInstance().GetRenderer()->AddShader(ResourceManager::GetInstance().GetShader("backgroundShader"));

	//-----------------------------add systems to scene-----------------------------//
	auto ecs = Application::GetInstance().GetECS();
	// TransformUpdator
	auto transformUpdator = std::make_unique<TransformUpdator>();
	ecs->addSystem(std::move(transformUpdator));

	// camera system
	auto cameraSystem = std::make_unique<CameraSystem>();
	ecs->addSystem(std::move(cameraSystem));
	// meshRenderer
	auto meshRenderer = std::make_unique<MeshRenderer>(ResourceManager::GetInstance().GetShader("PBR"));
	ecs->addSystem(std::move(meshRenderer));
	// IBL
	auto ibl = std::make_unique<IBL>(ResourceManager::GetInstance().GetShader("PBR"), ResourceManager::GetInstance().GetShader("backgroundShader"));
	ecs->addSystem(std::move(ibl));
	// AABB
	auto aabbCollision = std::make_unique<AABBCollision>();
	ecs->addSystem(std::move(aabbCollision));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = ecs->createEntity();
	ecs->addComponent<TransformComponent>(cameraEntity, TransformComponent(glm::vec3(20.0f, 5.0f, 20.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	ecs->addComponent<CameraComponent>(cameraEntity, CameraComponent());

	// sphere1
	auto sphere1 = ecs->createEntity();
	ecs->addComponent<TransformComponent>(sphere1, TransformComponent(glm::vec3(2.0f, 5.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	ecs->addComponent<MeshComponent>(sphere1, MeshComponent(ResourceManager::GetInstance().GetMesh("sphere")));
	ecs->addComponent<MaterialComponent>(sphere1, MaterialComponent(glm::vec3(0.0, 0.0, 1.0), 0.0, 0.0, 1.0));

	// sphere2
	auto sphere2 = ecs->createEntity();
	ecs->addComponent<TransformComponent>(sphere2, TransformComponent(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	ecs->addComponent<MeshComponent>(sphere2, MeshComponent(ResourceManager::GetInstance().GetMesh("sphere")));
	ecs->addComponent<MaterialComponent>(sphere2, MaterialComponent(glm::vec3(0.0, 0.0, 1.0), 0.0, 0.0, 1.0));

	// suzanne
	auto suzanne = ecs->createEntity();
	ecs->addComponent<TransformComponent>(suzanne, TransformComponent(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	ecs->addComponent<MeshComponent>(suzanne, MeshComponent(ResourceManager::GetInstance().GetMesh("suzanne")));
	ecs->addComponent<MaterialComponent>(suzanne, MaterialComponent(glm::vec3(0.0, 0.0, 1.0), 0.0, 0.0, 1.0));

	// init
	ecs->init();
}

void Scene3D::Update(float dt) {
	auto ecs = Application::GetInstance().GetECS();
	ecs->update(dt);
}

void Scene3D::Draw() {
	auto ecs = Application::GetInstance().GetECS();
	ecs->draw();
}