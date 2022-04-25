#include "Kikurage/Scene/Scene3D.h"

//------------Resource------------
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"
#include "Kikurage/Core/Event.h"

//------------Systems------------
#include "Kikurage/Systems/MeshRenderer/MeshRenderer.h"
#include "Kikurage/Systems/Camera/CameraSystem.h"
#include "Kikurage/Systems/IBL/IBL.h"
#include "Kikurage/Systems/Physics/Physics.h"
#include "Kikurage/Systems/Collision/CollisionSystem.h"
#include "Kikurage/Systems/Collision/SphereCollider.h"
#include "Kikurage/Systems/Collision/PlaneCollider.h"
#include "Kikurage/Systems/HandTracking/HandTracking.h"

//------------Components------------
#include "Kikurage/Components/CameraComponent.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/MeshComponent.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Components/RigidBodyComponent.h"
#include "Kikurage/Components/CollisionComponent.h"
#include "Kikurage/Components/IOControllerComponent.h"

Scene3D::Scene3D(Window* window) : m_window(window) {
	Init();
}

Scene3D::~Scene3D() {
	delete m_scene;
	delete renderer;
}

void Scene3D::Init() {
	//-------------------------------add scene & renderer-------------------------------//
	auto entityManager = std::make_unique<EntityManager>();
	m_scene = new Scene(std::move(entityManager));
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
	// Tracking
	auto handTracking = std::make_unique<HandTracking>();
	m_scene->addSystem(std::move(handTracking));

	//---------------------------------add entities---------------------------------//
	// camera
	auto cameraEntity = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(cameraEntity, TransformComponent(glm::vec3(20.0f, 5.0f, 20.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	m_scene->addComponent<CameraComponent>(cameraEntity, CameraComponent());

	// plane
	auto plane = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(plane, TransformComponent(glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(5.0f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(plane, MeshComponent(ResourceManager::GetMesh("plane")));
	m_scene->addComponent<MaterialComponent>(plane, MaterialComponent());
	m_scene->addComponent<RigidBodyComponent>(plane, RigidBodyComponent(false, true));
	m_scene->addComponent<CollisionComponent>(plane, CollisionComponent(new PlaneCollider(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f)));

	// hand0
	auto hand0 = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(hand0, TransformComponent(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(hand0, MeshComponent(ResourceManager::GetMesh("sphere")));
	m_scene->addComponent<MaterialComponent>(hand0, MaterialComponent(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1.0f));
	m_scene->addComponent<RigidBodyComponent>(hand0, RigidBodyComponent(false, false));
	m_scene->addComponent<CollisionComponent>(hand0, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));
	m_scene->addComponent<IOControllerComponent>(hand0, IOControllerComponent(Finger::Thumb, Bone::Distal));

	// hand1
	auto hand1 = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(hand1, TransformComponent(glm::vec3(20.0f, 10.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(hand1, MeshComponent(ResourceManager::GetMesh("sphere")));
	m_scene->addComponent<MaterialComponent>(hand1, MaterialComponent(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1.0f));
	m_scene->addComponent<RigidBodyComponent>(hand1, RigidBodyComponent(false, false));
	m_scene->addComponent<CollisionComponent>(hand1, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));
	m_scene->addComponent<IOControllerComponent>(hand1, IOControllerComponent(Finger::Index, Bone::Distal));

	// hand2
	auto hand2 = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(hand2, TransformComponent(glm::vec3(30.0f, 10.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(hand2, MeshComponent(ResourceManager::GetMesh("sphere")));
	m_scene->addComponent<MaterialComponent>(hand2, MaterialComponent(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1.0f));
	m_scene->addComponent<RigidBodyComponent>(hand2, RigidBodyComponent(false, false));
	m_scene->addComponent<CollisionComponent>(hand2, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));
	m_scene->addComponent<IOControllerComponent>(hand2, IOControllerComponent(Finger::Middle, Bone::Distal));

	// hand3
	auto hand3 = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(hand3, TransformComponent(glm::vec3(40.0f, 10.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(hand3, MeshComponent(ResourceManager::GetMesh("sphere")));
	m_scene->addComponent<MaterialComponent>(hand3, MaterialComponent(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1.0f));
	m_scene->addComponent<RigidBodyComponent>(hand3, RigidBodyComponent(false, false));
	m_scene->addComponent<CollisionComponent>(hand3, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));
	m_scene->addComponent<IOControllerComponent>(hand3, IOControllerComponent(Finger::Ring, Bone::Distal));

	// hand4
	auto hand4 = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(hand4, TransformComponent(glm::vec3(50.0f, 10.0f, 0.0f), glm::vec3(0.5f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(hand4, MeshComponent(ResourceManager::GetMesh("sphere")));
	m_scene->addComponent<MaterialComponent>(hand4, MaterialComponent(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f, 1.0f));
	m_scene->addComponent<RigidBodyComponent>(hand4, RigidBodyComponent(false, false));
	m_scene->addComponent<CollisionComponent>(hand4, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));
	m_scene->addComponent<IOControllerComponent>(hand4, IOControllerComponent(Finger::Pinky, Bone::Distal));

	// sphere
	auto bigSphere = m_scene->createEntity();
	m_scene->addComponent<TransformComponent>(bigSphere, TransformComponent(glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(3.0f), glm::vec3(0.0f)));
	m_scene->addComponent<MeshComponent>(bigSphere, MeshComponent(ResourceManager::GetMesh("sphere")));
	m_scene->addComponent<MaterialComponent>(bigSphere, MaterialComponent());
	m_scene->addComponent<RigidBodyComponent>(bigSphere, RigidBodyComponent(true, false));
	m_scene->addComponent<CollisionComponent>(bigSphere, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));

	// init
	m_scene->init();
}

void Scene3D::Update(float dt) {
	auto new_width = m_window->GetWidth();
	auto new_height = m_window->GetHeight();
	if (m_width != new_width || m_height != new_height) {
		m_width = new_width;
		m_height = new_height;
		WindowResizeEvent event(m_width, m_height);
		Event::publish(&event);
	}

	if (m_window->IsKeyPressed(GLFW_KEY_X)) {
		auto sphere = m_scene->createEntity();
		m_scene->addComponent<TransformComponent>(sphere, TransformComponent(glm::vec3((float)rand() / RAND_MAX * 2, 10.0f, (float)rand() / RAND_MAX * 2), glm::vec3(1.0f), glm::vec3(0.0f)));
		m_scene->addComponent<MeshComponent>(sphere, MeshComponent(ResourceManager::GetMesh("sphere")));
		m_scene->addComponent<MaterialComponent>(sphere, MaterialComponent(glm::vec3((float)rand() / RAND_MAX, rand() % 2, (float)rand() / RAND_MAX), (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f));
		m_scene->addComponent<RigidBodyComponent>(sphere, RigidBodyComponent(true, false));
		m_scene->addComponent<CollisionComponent>(sphere, CollisionComponent(new SphereCollider(glm::vec3(0.0f), 1.0f)));
	}
	m_scene->update(dt);
}

void Scene3D::Draw() {
	renderer->BindFBO();
	m_scene->draw();
	renderer->UnbindFBO();

	m_window->Draw(renderer->GetRenderTexture());
}