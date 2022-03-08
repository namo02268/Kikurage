#include "CameraSystem.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TransformComponent.h"
#include "CameraComponent.h"

CameraSystem::CameraSystem(Window* window, Shader shader) {
	this->m_window = window;
	this->m_shader = shader;
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CameraComponent>();
	m_requiredComponent[family] = true;
}

CameraSystem::~CameraSystem() {

}

void CameraSystem::init() {

}

void CameraSystem::update(float dt) {
	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& cameraComponent = m_parentScene->getComponent<CameraComponent>(e);

		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(cameraComponent.Yaw)) * cos(glm::radians(cameraComponent.Pitch));
		front.y = sin(glm::radians(cameraComponent.Pitch));
		front.z = sin(glm::radians(cameraComponent.Yaw)) * cos(glm::radians(cameraComponent.Pitch));
		cameraComponent.Front = glm::normalize(front);

		// also re-calculate the Right and Up vector
		cameraComponent.Right = glm::normalize(glm::cross(cameraComponent.Front, cameraComponent.WorldUp));
		cameraComponent.Up = glm::normalize(glm::cross(cameraComponent.Right, cameraComponent.Front));

		// key input
		float velocity = cameraComponent.MovementSpeed * dt;
		if (m_window->IsKeyPressed(GLFW_KEY_W))
			transfromComponent.position += cameraComponent.Front * velocity;
		if (m_window->IsKeyPressed(GLFW_KEY_S))
			transfromComponent.position -= cameraComponent.Front * velocity;
		if (m_window->IsKeyPressed(GLFW_KEY_A))
			transfromComponent.position -= cameraComponent.Right * velocity;
		if (m_window->IsKeyPressed(GLFW_KEY_D))
			transfromComponent.position += cameraComponent.Right * velocity;
		if (m_window->IsKeyPressed(GLFW_KEY_SPACE))
			transfromComponent.position += cameraComponent.Up * velocity;
		if (m_window->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
			transfromComponent.position -= cameraComponent.Up * velocity;

		// mouse input
		if (m_window->IsMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
			glm::vec2 mousePos = m_window->GetCursorPosition();
			if (firstMouse)
			{
				lastX = mousePos.x;
				lastY = mousePos.y;
				firstMouse = false;
//				std::cout << "first mouse" << std::endl;
			}


			m_window->disableMouseCursor();
			float xoffset = mousePos.x - lastX;
			float yoffset = lastY - mousePos.y;
//			std::cout << xoffset << " : " << mousePos.x << " : " << lastX << std::endl;

			lastX = mousePos.x;
			lastY = mousePos.y;

			xoffset *= cameraComponent.MouseSensitivity;
			yoffset *= cameraComponent.MouseSensitivity;

			cameraComponent.Yaw += xoffset;
			cameraComponent.Pitch += yoffset;

			if (cameraComponent.constrainPitch) {
				if (cameraComponent.Pitch > 89.0f)
					cameraComponent.Pitch = 89.0f;
				if (cameraComponent.Pitch < -89.0f)
					cameraComponent.Pitch = -89.0f;
			}
		}
		else {
			firstMouse = true;
			m_window->normalMouseCursor();
		}
	}
}

void CameraSystem::draw() {
	this->m_shader.Use();
	for (auto& e : m_entityArray) {
		auto& transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto& cameraComponent = m_parentScene->getComponent<CameraComponent>(e);

		glm::mat4 projection = glm::perspective(glm::radians(cameraComponent.Zoom), (float)m_window->GetWidth() / (float)m_window->GetHeight(), 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(transfromComponent.position, transfromComponent.position + cameraComponent.Front, cameraComponent.Up);

		this->m_shader.SetVector3f("cameraPos", transfromComponent.position);
		this->m_shader.SetMatrix4("projection", projection);
		this->m_shader.SetMatrix4("view", view);
	}
}