#include "Kikurage/Scene/Scene3D.h"

//------------Resource------------
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

//------------Systems------------
#include "Kikurage/Systems/MeshRenderer/MeshRenderer.h"
#include "Kikurage/Systems/Camera/CameraSystem.h"
#include "Kikurage/Systems/IBL/IBL.h"
#include "Kikurage/Systems/Physics/Physics.h"
#include "Kikurage/Systems/Collision/CollisionSystem.h"
#include "Kikurage/Systems/Collision/SphereCollider.h"
#include "Kikurage/Systems/Collision/PlaneCollider.h"

//------------Components------------
#include "Kikurage/Components/CameraComponent.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Components/RigidBodyComponent.h"
#include "Kikurage/Components/CollisionComponent.h"

Scene3D::Scene3D(Window* window) : m_window(window) {
	Init();
}

Scene3D::~Scene3D() {
	delete m_scene;
	delete renderer;
}

void Scene3D::Init() {
	//-------------------------------add scene-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_unique<EventHandler>();
	m_scene = new Scene(std::move(entityManager), std::move(eventHandler));

	renderer = new Renderer();

	//-----------------------------------Resources-----------------------------------//
	stbi_set_flip_vertically_on_load(true);

	ResourceManager::LoadShaderFromFile("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
	ResourceManager::LoadShaderFromFile("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
	ResourceManager::LoadMeshFromFile("resources/objects/suzanne/suzanne.obj", "suzanne");
	ResourceManager::LoadMeshFromFile("resources/objects/sphere/sphere.obj", "sphere");
	ResourceManager::LoadMeshFromFile("resources/objects/plane/plane.obj", "plane");

	//-----------------------------add systems to scene-----------------------------//
	// camera system
	auto cameraSystem = std::make_unique<CameraSystem>(m_window);
	cameraSystem->addShader(ResourceManager::GetShader("PBR"));
	cameraSystem->addShader(ResourceManager::GetShader("backgroundShader"));
	m_scene->addSystem(std::move(cameraSystem));
	// meshRenderer
	auto meshRenderer = std::make_unique<MeshRenderer>(ResourceManager::GetShader("PBR"));
	m_scene->addSystem(std::move(meshRenderer));
	// IBL
	auto ibl = std::make_unique<IBL>(ResourceManager::GetShader("PBR"), ResourceManager::GetShader("backgroundShader"));
	m_scene->addSystem(std::move(ibl));
	// Physics
	auto physics = std::make_unique<Physics>();
	m_scene->addSystem(std::move(physics));
	// Collision 
	auto collisionSystem = std::make_unique<CollisionSystem>();
	m_scene->addSystem(std::move(collisionSystem));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(cameraEntity, glm::vec3(20.0f, 5.0f, 20.0f), glm::vec3(1.0f), glm::vec3(0.0f));
	m_scene->addComponent<CameraComponent>(cameraEntity);

	// plane
	auto plane = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(plane, glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(3.0f), glm::vec3(0.0f));
	m_scene->addComponent<MeshComponent>(plane, ResourceManager::GetMesh("plane"));
	m_scene->addComponent<MaterialComponent>(plane);
	m_scene->addComponent<RigidBodyComponent>(plane, false, true);
	m_scene->addComponent<CollisionComponent>(plane, new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));

	// init
	m_scene->init();
}

void Scene3D::Update(float dt) {
	if (m_window->IsKeyPressed(GLFW_KEY_X)) {
		auto sphere = m_scene->createEntity();
		m_scene->addComponent<TransformComponent>(sphere, glm::vec3((float)rand() / RAND_MAX * 2, 10.0f, (float)rand() / RAND_MAX * 2), glm::vec3(1.0f), glm::vec3(0.0f));
		m_scene->addComponent<MeshComponent>(sphere, ResourceManager::GetMesh("sphere"));
		m_scene->addComponent<MaterialComponent>(sphere, glm::vec3((float)rand() / RAND_MAX, rand() % 2, (float)rand() / RAND_MAX), (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f);
		m_scene->addComponent<RigidBodyComponent>(sphere, true, false);
		m_scene->addComponent<CollisionComponent>(sphere, new SphereCollider(glm::vec3(0.0f), 1.0f));
	}
	m_scene->update(dt);
}

void Scene3D::Draw() {
	renderer->BindFBO();
	m_scene->draw();
	renderer->UnbindFBO();

	m_window->Draw(renderer->GetRenderTexture());
}