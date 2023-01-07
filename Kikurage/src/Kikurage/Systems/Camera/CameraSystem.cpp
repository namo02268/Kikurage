#include "Kikurage/Systems/Camera/CameraSystem.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/CameraComponent.h"

namespace Kikurage {
	CameraSystem::CameraSystem() {
		auto family = getComponentTypeID<Transform>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<CameraComponent>();
		m_requiredComponent[family] = true;
	}

	CameraSystem::~CameraSystem() {

	}

	void CameraSystem::Init() {

	}

	void CameraSystem::Update(float dt) {
		for (auto& e : m_entityArray) {
			auto trans = m_parentScene->GetComponent<Transform>(e);
			camera.UpdateProjectionMatrix();
			camera.HandleKeyboard(*trans, dt);
			camera.HandleMouse(*trans, dt);

			Application::GetInstance().GetRenderer()->BindCameraInformation(camera, *trans);
		}
	}

	void CameraSystem::Draw() {
	}
}
