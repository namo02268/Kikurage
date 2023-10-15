#include "Kikurage/Scene/Scene3D.h"
#include "Kikurage/Core/Application/Application.h"
#include "Nameko/ECS.h"

//------------Resource------------//
#include "stb_image/stb_image.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"
#include "Kikurage/Resource/Model/ModelLoader.h"

//------------Components------------//
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Name/Name.h"
#include "Kikurage/Components/Camera/Camera.h"
#include "Kikurage/Components/Light/Light.h"

//------------Systems------------//
#include "Kikurage/Systems/TransformUpdater/TransformUpdater.h"
#include "Kikurage/Systems/Renderer/MeshRenderer.h"
#include "Kikurage/Systems/Camera/CameraController.h"
#include "Kikurage/Systems/Lighting/Lighting.h"

namespace Kikurage {
	Scene3D::Scene3D() {
	}

	Scene3D::~Scene3D() {
	}

	void Scene3D::Init() {
		//-----------------------------add systems to scene-----------------------------//
		auto ecs = Application::GetInstance().GetECS();
		// transform updater
		auto transformUpdater = std::make_unique<TransformUpdater>();
		ecs->AddSystem(std::move(transformUpdater));
		// camera system
		auto cameraSystem = std::make_unique<CameraController>();
		ecs->AddSystem(std::move(cameraSystem));
		// meshRenderer
		auto meshRenderer = std::make_unique<MeshRenderer>();
		ecs->AddSystem(std::move(meshRenderer));
		// Lighting
		auto lighting = std::make_unique<Lighting>();
		ecs->AddSystem(std::move(lighting));

		//---------------------------------add entities---------------------------------//
		// camera
		auto cameraEntity = ecs->CreateEntity();
		ecs->AddComponent<Transform>(cameraEntity, Transform(Vector3(50.0f, 5.0f, 0.0f), Vector3(1.0f), Vector3(0.0f, 90.0f, 0.0f)));
		ecs->AddComponent<Camera>(cameraEntity, Camera());
		ecs->GetComponent<Name>(cameraEntity)->Rename("Camera");

		// Light
		constexpr unsigned int NR_LIGHTS = 32;
		srand(13);
		for (unsigned int i = 0; i < NR_LIGHTS; i++) {
			auto light = ecs->CreateEntity();
			float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0) * 10.0f;
			float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0) * 10.0f;
			float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0) * 10.0f;
			ecs->AddComponent<Transform>(light, Transform(Vector3(xPos, yPos, zPos), Vector3(0.25f), Vector3(0.0f)));
			float r = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			float g = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			float b = static_cast<float>(((rand() % 100) / 200.0f) + 0.5);
			ecs->AddComponent<Light>(light, Light(Vector3(r, g, b)));
			char name[64];
			sprintf_s(name, "Light_%d", i);
			ecs->GetComponent<Name>(light)->Rename(name);
		}

		// sphere
//		ModelLoader::LoadEntity("resources/objects/sphere/sphere.obj", 1.0f);

		// suponza
		ModelLoader::LoadEntity("resources/objects/Sponza/glTF/Sponza.gltf", 0.1f);

		// Cube
//		ModelLoader::LoadEntity("resources/objects/cube/cube.obj", 1.0f);

		// backpack
		/*
		auto backpack0 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack0)->Rename("backpack_0");

		auto backpack1 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack1)->Rename("backpack_1");

		auto backpack2 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack2)->Rename("backpack_2");

		auto backpack3 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack3)->Rename("backpack_3");

		auto backpack4 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack4)->Rename("backpack_4");

		auto backpack5 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack5)->Rename("backpack_5");

		auto backpack6 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack6)->Rename("backpack_6");

		auto backpack7 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack7)->Rename("backpack_7");

		auto backpack8 = ModelLoader::LoadEntity("resources/objects/backpack/backpack.obj", 1.0f);
		ecs->GetComponent<Name>(backpack8)->Rename("backpack_8");
		*/

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
