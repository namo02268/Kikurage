#include "Kikurage/Scene/Scene3D.h"
#include "Kikurage/Core/Application/Application.h"
#include "Nameko/ECS.h"

//------------Resource------------
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"
#include "Kikurage/Resource/Model/ModelLoader.h"

//------------Systems------------
#include "Kikurage/Systems/TransformUpdater/TransformUpdater.h"
#include "Kikurage/Systems/Renderer/MeshRenderer.h"
#include "Kikurage/Systems/Camera/CameraController.h"
#include "Kikurage/Systems/IBL/IBL.h"
#include "Kikurage/Systems/AABBCollision/AABBCollision.h"

//------------Components------------
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/RigidBodyComponent.h"

namespace Kikurage {
	Scene3D::Scene3D() {
	}

	Scene3D::~Scene3D() {
	}

	void Scene3D::Init() {
//		ResourceManager::LoadShader("resources/shaders/Simple.vert", "resources/shaders/PBR_nonTexture.frag", nullptr, "PBR");
//		ResourceManager::LoadShader("resources/shaders/Simple.vert", "resources/shaders/depth.frag", nullptr, "PBR");
//		ResourceManager::LoadShader("resources/shaders/Simple.vert", "resources/shaders/normal.frag", nullptr, "PBR");
//		ResourceManager::LoadShader("resources/shaders/background.vert", "resources/shaders/background.frag", nullptr, "backgroundShader");
		ResourceManager::LoadShader("resources/shaders/gBuffer.vert", "resources/shaders/gBuffer.frag", nullptr, "PBR");

		Application::GetInstance().GetRenderer()->AddShader(ResourceManager::GetShader("PBR"));
//		Application::GetInstance().GetRenderer()->AddShader(ResourceManager::GetShader("backgroundShader"));

		//-----------------------------add systems to scene-----------------------------//
		auto ecs = Application::GetInstance().GetECS();
		// transform updater
		auto transformUpdater = std::make_unique<TransformUpdater>();
		ecs->AddSystem(std::move(transformUpdater));
		// camera system
		auto cameraSystem = std::make_unique<CameraController>();
		ecs->AddSystem(std::move(cameraSystem));
		// meshRenderer
		auto meshRenderer = std::make_unique<MeshRenderer>(ResourceManager::GetShader("PBR"));
		ecs->AddSystem(std::move(meshRenderer));

		//---------------------------------add entities---------------------------------//
		// camera
		auto cameraEntity = ecs->CreateEntity();
		ecs->AddComponent<Transform>(cameraEntity, Transform(Vector3(50.0f, 5.0f, 0.0f), Vector3(1.0f), Vector3(0.0f, 90.0f, 0.0f)));
		ecs->AddComponent<Camera>(cameraEntity, Camera());
//		ecs->GetComponent<Name>(cameraEntity)->Rename("EditorCamera");

		// sphere
//		ModelLoader::LoadEntity("resources/objects/sphere/sphere.obj", 1.0f);

		// suponza
		ModelLoader::LoadEntity("resources/objects/Sponza/glTF/Sponza.gltf", 0.1f);

		// backpack
//		ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);

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
