#include "Kikurage/Core/Renderer/EditorCamera.h"
#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	void EditorCamera::HandleMouse(Transform& transform, float dt) {
		static bool mouseHeld = false;
		Vector2 rotateVelocity{ 0.0f };
		auto window = Application::GetInstance().GetWindow();

		if (window->IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			mouseHeld = true;
			window->disableMouseCursor();
			m_prevCursorPos = { window->GetCursorPos()[0], window->GetCursorPos()[1] };
		}

		if (window->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
			auto xpos = window->GetCursorPos()[0];
			auto ypos = window->GetCursorPos()[1];
			rotateVelocity = Vector2((xpos - m_prevCursorPos.x), (ypos - m_prevCursorPos.y)) * m_mouseSensitivity;
			Quaternion rotation = transform.GetLocalOrientation();
			Quaternion rotationX = AngleAxis(rotateVelocity.y, Vector3(1.0f, 0.0f, 0.0f));
			Quaternion rotationY = AngleAxis(rotateVelocity.x, Vector3(0.0f, 1.0f, 0.0f));

			rotation = rotationY * rotation;
			rotation = rotation * rotationX;
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

	void EditorCamera::HandleKeyboard(Transform& transform, float dt) {
		auto speed = m_cameraSpeed * dt;
		auto window = Application::GetInstance().GetWindow();
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

	void EditorCamera::HandleScroll(Transform& transform, float offset, float dt) {

	}
}
