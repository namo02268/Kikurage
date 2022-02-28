#include "CameraSystem.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "CameraComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CameraSystem::CameraSystem(Shader shader, Window* window) {
	this->m_shader = shader;
	this->window = window;
	this->m_width = window->GetWidth();
	this->m_height = window->GetHeight();

	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CameraComponent>();
	m_requiredComponent[family] = true;

}

CameraSystem::~CameraSystem() {

}

void CameraSystem::init() {

}

void CameraSystem::update() {
	this->m_width = window->GetWidth();
	this->m_height = window->GetHeight();
}

void CameraSystem::draw() {
	for (auto& e : m_entityArray) {
		auto size = parentScene->getComponent<CameraComponent>(e).size;
		auto position = parentScene->getComponent<TransformComponent>(e).position;
		glm::mat4 projection = glm::ortho(-m_width / m_height * size + position.x, m_width / m_height * size + position.x, size + position.y, -size + position.y, -1.0f, 1.0f);
		this->m_shader.SetMatrix4("projection", projection);
	}
}