#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Systems/Renderer/CameraController.h"
#include "Kikurage/Core/Event.h"

CameraController::CameraController() {
}

void CameraController::CameraInputUpdate() {
	// TODO : ADD KEY_MAP
	auto window = Application::GetInstance().GetWindow();

	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
	front.y = sin(glm::radians(camera.Pitch));
	front.z = sin(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
	camera.Front = glm::normalize(front);

	// calculate the Right and Up vector
	camera.Right = glm::normalize(glm::cross(camera.Front, camera.WorldUp));
	camera.Up = glm::normalize(glm::cross(camera.Right, camera.Front));

	// key input
	float velocity = camera.MovementSpeed * Application::GetInstance().GetDeltaTime();
	if (window->IsKeyHeld(GLFW_KEY_W))
		camera.position += camera.Front * velocity;
	if (window->IsKeyHeld(GLFW_KEY_S))
		camera.position -= camera.Front * velocity;
	if (window->IsKeyHeld(GLFW_KEY_A))
		camera.position -= camera.Right * velocity;
	if (window->IsKeyHeld(GLFW_KEY_D))
		camera.position += camera.Right * velocity;
	if (window->IsKeyHeld(GLFW_KEY_SPACE))
		camera.position += camera.Up * velocity;
	if (window->IsKeyHeld(GLFW_KEY_LEFT_SHIFT))
		camera.position -= camera.Up * velocity;

	// mouse input
	static bool firstMouse = true;
	static float lastX = 0.0f;
	static float lastY = 0.0f;

	if (window->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
		auto mousePos = window->GetCursorPos();
		if (firstMouse)
		{
			lastX = mousePos[0];
			lastY = mousePos[1];
			firstMouse = false;
		}


		window->disableMouseCursor();
		float xoffset = mousePos[0] - lastX;
		float yoffset = lastY - mousePos[1];

		lastX = mousePos[0];
		lastY = mousePos[1];

		xoffset *= camera.MouseSensitivity;
		yoffset *= camera.MouseSensitivity;

		camera.Yaw += xoffset;
		camera.Pitch += yoffset;

		if (camera.constrainPitch) {
			if (camera.Pitch > 89.0f)
				camera.Pitch = 89.0f;
			if (camera.Pitch < -89.0f)
				camera.Pitch = -89.0f;
		}
	}
	else {
		firstMouse = true;
		window->normalMouseCursor();
	}
}
