#include "Kikurage/Systems/Camera/CameraController.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Camera/CameraComponent.h"

namespace Kikurage {
	CameraController::CameraController() {
	}

	CameraController::~CameraController() {
	}

	void CameraController::Init() {
	}

	void CameraController::Update(float dt) {
		m_ecs->Each<CameraComponent, Transform>([&](CameraComponent, Transform& transform) {
			camera.UpdateProjectionMatrix();
			camera.HandleKeyboard(transform, dt);
			camera.HandleMouse(transform, dt);

			Application::GetInstance().GetRenderer()->BindCameraInformation(camera, transform);
		});
	}

	void CameraController::Draw() {
	}
}
