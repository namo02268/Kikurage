#include "Systems/Camera/CameraSystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ECS/Scene.h"
#include "Components/TransformComponent.h"
#include "Components/cameraComponent.h"

CameraSystem::CameraSystem(Window* window) {
	this->m_window = window;
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CameraComponent>();
	m_requiredComponent[family] = true;
}

CameraSystem::~CameraSystem() {

}

void CameraSystem::addShader(Shader* shader) {
	m_shaders.push_back(shader);
}

void CameraSystem::init() {

}

void CameraSystem::update(float dt) {
	for (auto& e : m_entityArray) {
		auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto cameraComponent = m_parentScene->getComponent<CameraComponent>(e);

		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(cameraComponent->Yaw)) * cos(glm::radians(cameraComponent->Pitch));
		front.y = sin(glm::radians(cameraComponent->Pitch));
		front.z = sin(glm::radians(cameraComponent->Yaw)) * cos(glm::radians(cameraComponent->Pitch));
		cameraComponent->Front = glm::normalize(front);

		// also re-calculate the Right and Up vector
		cameraComponent->Right = glm::normalize(glm::cross(cameraComponent->Front, cameraComponent->WorldUp));
		cameraComponent->Up = glm::normalize(glm::cross(cameraComponent->Right, cameraComponent->Front));

		// key input
		float velocity = cameraComponent->MovementSpeed * dt;
		if (m_window->IsKeyHeld(GLFW_KEY_W))
			transfromComponent->position += cameraComponent->Front * velocity;
		if (m_window->IsKeyHeld(GLFW_KEY_S))
			transfromComponent->position -= cameraComponent->Front * velocity;
		if (m_window->IsKeyHeld(GLFW_KEY_A))
			transfromComponent->position -= cameraComponent->Right * velocity;
		if (m_window->IsKeyHeld(GLFW_KEY_D))
			transfromComponent->position += cameraComponent->Right * velocity;
		if (m_window->IsKeyHeld(GLFW_KEY_SPACE))
			transfromComponent->position += cameraComponent->Up * velocity;
		if (m_window->IsKeyHeld(GLFW_KEY_LEFT_SHIFT))
			transfromComponent->position -= cameraComponent->Up * velocity;

		// mouse input
		if (m_window->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
			auto mousePos = m_window->GetCursorPos();
			if (firstMouse)
			{
				lastX = mousePos[0];
				lastY = mousePos[1];
				firstMouse = false;
//				std::cout << "first mouse" << std::endl;
			}


//			m_window->disableMouseCursor();
			float xoffset = mousePos[0] - lastX;
			float yoffset = lastY - mousePos[1];
//			std::cout << xoffset << " : " << mousePos.x << " : " << lastX << std::endl;

			lastX = mousePos[0];
			lastY = mousePos[1];

			xoffset *= cameraComponent->MouseSensitivity;
			yoffset *= cameraComponent->MouseSensitivity;

			cameraComponent->Yaw += xoffset;
			cameraComponent->Pitch += yoffset;

			if (cameraComponent->constrainPitch) {
				if (cameraComponent->Pitch > 89.0f)
					cameraComponent->Pitch = 89.0f;
				if (cameraComponent->Pitch < -89.0f)
					cameraComponent->Pitch = -89.0f;
			}
		}
		else {
			firstMouse = true;
//			m_window->normalMouseCursor();
		}
	}
}

void CameraSystem::draw() {
	glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());

	for (auto& e : m_entityArray) {
		auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto cameraComponent = m_parentScene->getComponent<CameraComponent>(e);

		glm::mat4 projection = glm::perspective(glm::radians(cameraComponent->Zoom), (float)m_window->GetWidth() / (float)m_window->GetHeight(), cameraComponent->Near, cameraComponent->Far);
		glm::mat4 view = glm::lookAt(transfromComponent->position, transfromComponent->position + cameraComponent->Front, cameraComponent->Up);

		for (auto& shader : m_shaders) {
			shader->Use();
			shader->SetVector3f("cameraPos", transfromComponent->position);
			shader->SetMatrix4("projection", projection);
			shader->SetMatrix4("view", view);
		}
	}
}