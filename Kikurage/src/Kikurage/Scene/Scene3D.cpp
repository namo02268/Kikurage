#include "Kikurage/Scene/Scene3D.h"
#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/ECS/ECS.h"

//------------Resource------------
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"
#include "Kikurage/Resource/Model/ModelLoader.h"

//------------Systems------------
#include "Kikurage/Systems/TransformUpdater/TransformUpdater.h"
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
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/RigidBodyComponent.h"
#include "Kikurage/Components/CollisionComponent.h"

namespace Kikurage {
	Scene3D::Scene3D() {
	}

	Scene3D::~Scene3D() {
	}

	void Scene3D::Init() {
		//-----------------------------------Resources-----------------------------------//
		stbi_set_flip_vertically_on_load(true);

		auto& resouceManager = ResourceManager::GetInstance();
//		resouceManager.LoadShader("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
		resouceManager.LoadShader("resources/shaders/Simple.vert", "resources/shaders/depth.frag", nullptr, "PBR");
		resouceManager.LoadShader("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");

		Application::GetInstance().GetRenderer()->AddShader(ResourceManager::GetInstance().GetShader("PBR"));
		Application::GetInstance().GetRenderer()->AddShader(ResourceManager::GetInstance().GetShader("backgroundShader"));

		//-----------------------------add systems to scene-----------------------------//
		auto ecs = Application::GetInstance().GetECS();
		// transform updater
		auto transformUpdater = std::make_unique<TransformUpdater>();
		ecs->AddSystem(std::move(transformUpdater));
		// camera system
		auto cameraSystem = std::make_unique<CameraSystem>();
		ecs->AddSystem(std::move(cameraSystem));
		// meshRenderer
		auto meshRenderer = std::make_unique<MeshRenderer>(ResourceManager::GetInstance().GetShader("PBR"));
		ecs->AddSystem(std::move(meshRenderer));
		// IBL
		auto ibl = std::make_unique<IBL>(ResourceManager::GetInstance().GetShader("PBR"), ResourceManager::GetInstance().GetShader("backgroundShader"));
		ecs->AddSystem(std::move(ibl));
		// AABB
//		auto aabbCollision = std::make_unique<AABBCollision>();
//		ecs->AddSystem(std::move(aabbCollision));

		//---------------------------------add entities---------------------------------//
		// camera
		auto cameraEntity = ecs->CreateEntity();
		ecs->AddComponent<Transform>(cameraEntity, Transform(Vector3(50.0f, 5.0f, 0.0f), Vector3(1.0f), Vector3(0.0f, 90.0f, 0.0f)));
		ecs->AddComponent<CameraComponent>(cameraEntity, CameraComponent());
		ecs->GetComponent<Name>(cameraEntity)->Rename("EditorCamera");

		// sphere
//		ModelLoader::LoadEntity("resources/objects/sphere/sphere.obj", 1.0f);

		// suponza
		ModelLoader::LoadEntity("resources/objects/sponza/sponza.obj", 0.1f);

		// init
		ecs->Init();
	}

	void Scene3D::Update(float dt) {
		auto ecs = Application::GetInstance().GetECS();
		ecs->Update(dt);
	}

	void Scene3D::Draw() {
		auto ecs = Application::GetInstance().GetECS();
		ecs->Draw();
	}
}
