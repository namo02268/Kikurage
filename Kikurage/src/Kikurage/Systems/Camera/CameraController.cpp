#include "Kikurage/Systems/Camera/CameraController.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Camera/CameraComponent.h"

namespace Kikurage {
	CameraController::CameraController() {
		auto family = getComponentTypeID<Transform>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<CameraComponent>();
		m_requiredComponent[family] = true;
	}

	CameraController::~CameraController() {

	}

	void CameraController::Init() {

	}

	void CameraController::Update(float dt) {
		for (auto& e : m_entityArray) {
			auto trans = m_ecs->GetComponent<Transform>(e);
			camera.UpdateProjectionMatrix();
			camera.HandleKeyboard(*trans, dt);
			camera.HandleMouse(*trans, dt);

			Application::GetInstance().GetRenderer()->BindCameraInformation(camera, *trans);
		}
	}

	void CameraController::Draw() {
	}

	void CameraController::HandleMouse(Transform& transform, float dt) {

	}

	void CameraController::HandleKeyboard(Transform& transform, float dt) {

	}

	void CameraController::HandleScroll(Transform& transform, float dt){
	}
}
