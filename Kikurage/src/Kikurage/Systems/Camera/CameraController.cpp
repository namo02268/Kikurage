#include "Kikurage/Systems/Camera/CameraController.h"
#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	CameraController::CameraController() {}
	CameraController::~CameraController() {}

	void CameraController::Init() {}

	void CameraController::Update(float dt) {
		m_ecs->EachComponent<Camera, Transform>([&](Camera& camera, Transform& transform) {
			camera.UpdateProjectionMatrix();
			HandleMouse(transform, camera, dt);
			HandleKeyboard(transform, camera, dt);
			Application::GetInstance().GetRenderer()->BindCameraInformation(camera, transform);
		});
	}

	void CameraController::Draw(){}

	void CameraController::HandleMouse(Transform& transform, Camera& camera, float dt) {
		auto window = Application::GetInstance().GetWindow();
		static bool mouseHeld = false;
		Vector2 rotateVelocity{ 0.0f };

		if (window->IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			mouseHeld = true;
			m_prevCursorPos = { window->GetCursorPos()[0], window->GetCursorPos()[1] };
		}

		if (window->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
			auto xpos = window->GetCursorPos()[0];
			auto ypos = window->GetCursorPos()[1];
			rotateVelocity = Vector2((xpos - m_prevCursorPos.x), (ypos - m_prevCursorPos.y)) * camera.GetMouseSensitivity();
			Quaternion rotation = transform.GetLocalOrientation();
			Quaternion rotationX = AngleAxis(rotateVelocity.y, VectorRight);
			Quaternion rotationY = AngleAxis(rotateVelocity.x, VectorUp);

			rotation = rotationY * rotation * rotationX;
			transform.SetRotation(rotation);
			m_prevCursorPos = Vector2(xpos, ypos);
		}
		else {
			if (mouseHeld) {
				mouseHeld = false;
				window->normalMouseCursor();
			}
		}
	}

	void CameraController::HandleKeyboard(Transform& transform, Camera& camera, float dt) {
		auto window = Application::GetInstance().GetWindow();
		auto speed = camera.GetCameraSpeed() * dt;

		Vector3 velocity{ 0.0f };
		if (window->IsKeyHeld(GLFW_KEY_W)) {
			velocity -= transform.GetForwardDirection() * speed;
		}
		if (window->IsKeyHeld(GLFW_KEY_S)) {
			velocity += transform.GetForwardDirection() * speed;
		}
		if (window->IsKeyHeld(GLFW_KEY_A)) {
			velocity -= transform.GetRightDirection() * speed;
		}
		if (window->IsKeyHeld(GLFW_KEY_D)) {
			velocity += transform.GetRightDirection() * speed;
		}
		if (window->IsKeyHeld(GLFW_KEY_LEFT_SHIFT)) {
			velocity -= transform.GetUpDirection() * speed;
		}
		if (window->IsKeyHeld(GLFW_KEY_SPACE)) {
			velocity += transform.GetUpDirection() * speed;
		}

		transform.Translate(velocity * dt);
	}

	void CameraController::HandleScroll(Transform& transform, Camera& camera, float offset, float dt){}
}