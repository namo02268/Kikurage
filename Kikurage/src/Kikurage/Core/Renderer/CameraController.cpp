#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Core/Renderer/CameraController.h"
#include "Kikurage/Core/Event.h"

CameraController::CameraController() {
}

void CameraController::SetShader(Shader* shader) {
	m_shaders.push_back(shader);
}

void CameraController::RemoveShader(Shader* shader) {
	m_shaders.erase(std::remove(m_shaders.begin(), m_shaders.end(), shader));
}

void CameraController::CameraInputUpdate() {
	// TODO : ADD KEY_MAP
	auto window = Application::GetInstance().GetWindow();

	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(mainCamera.Yaw)) * cos(glm::radians(mainCamera.Pitch));
	front.y = sin(glm::radians(mainCamera.Pitch));
	front.z = sin(glm::radians(mainCamera.Yaw)) * cos(glm::radians(mainCamera.Pitch));
	mainCamera.Front = glm::normalize(front);

	// calculate the Right and Up vector
	mainCamera.Right = glm::normalize(glm::cross(mainCamera.Front, mainCamera.WorldUp));
	mainCamera.Up = glm::normalize(glm::cross(mainCamera.Right, mainCamera.Front));

	// key input
	float velocity = mainCamera.MovementSpeed * Application::GetInstance().GetDeltaTime();
	if (window->IsKeyHeld(GLFW_KEY_W))
		mainCamera.position += mainCamera.Front * velocity;
	if (window->IsKeyHeld(GLFW_KEY_S))
		mainCamera.position -= mainCamera.Front * velocity;
	if (window->IsKeyHeld(GLFW_KEY_A))
		mainCamera.position -= mainCamera.Right * velocity;
	if (window->IsKeyHeld(GLFW_KEY_D))
		mainCamera.position += mainCamera.Right * velocity;
	if (window->IsKeyHeld(GLFW_KEY_SPACE))
		mainCamera.position += mainCamera.Up * velocity;
	if (window->IsKeyHeld(GLFW_KEY_LEFT_SHIFT))
		mainCamera.position -= mainCamera.Up * velocity;

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

		xoffset *= mainCamera.MouseSensitivity;
		yoffset *= mainCamera.MouseSensitivity;

		mainCamera.Yaw += xoffset;
		mainCamera.Pitch += yoffset;

		if (mainCamera.constrainPitch) {
			if (mainCamera.Pitch > 89.0f)
				mainCamera.Pitch = 89.0f;
			if (mainCamera.Pitch < -89.0f)
				mainCamera.Pitch = -89.0f;
		}
	}
	else {
		firstMouse = true;
		window->normalMouseCursor();
	}
}
