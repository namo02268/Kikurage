#include "Kikurage/Core/Renderer/EditorCamera.h"
#include "Kikurage/Core/Application/Application.h"

void EditorCamera::HandleMouse(TransformComponent& transform, float dt) {
	static bool mouseHeld = false;
	auto rotateVelocity = glm::vec2(0.0f);
	auto window = Application::GetInstance().GetWindow();

	if (window->IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		mouseHeld = true;
		window->disableMouseCursor();
		m_prevCursorPos = { window->GetCursorPos()[0], window->GetCursorPos()[1] };
	}

	if (window->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
		auto xpos = window->GetCursorPos()[0];
		auto ypos = window->GetCursorPos()[1];
		rotateVelocity = glm::vec2((xpos - m_prevCursorPos.x), (ypos - m_prevCursorPos.y)) * m_mouseSensitivity;
		glm::quat rotation = transform.GetLocalOrientation();
		glm::quat rotationX = glm::angleAxis(rotateVelocity.y, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat rotationY = glm::angleAxis(rotateVelocity.x, glm::vec3(0.0f, 1.0f, 0.0f));

		rotation = rotationY * rotation;
		rotation = rotation * rotationX;
		transform.SetRotation(rotation);
		m_prevCursorPos = glm::vec2(xpos, ypos);
	}
	else {
		if (mouseHeld) {
			mouseHeld = false;
			window->normalMouseCursor();
		}
	}

}

void EditorCamera::HandleKeyboard(TransformComponent& transform, float dt) {
	auto speed = m_cameraSpeed * dt;
	auto velocity = glm::vec3(0.0f);
	auto window = Application::GetInstance().GetWindow();

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

	transform.position += velocity * dt;
}

void EditorCamera::HandleScroll(TransformComponent& transform, float offset, float dt) {

}