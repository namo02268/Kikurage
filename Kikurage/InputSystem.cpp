#include "InputSystem.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MotionComponent.h"
#include "InputComponent.h"

InputSystem::InputSystem(Window* window) {
	this->m_window = window;
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<MotionComponent>();
	m_requiredComponent[family] = true;family = getComponentTypeID<InputComponent>();
	m_requiredComponent[family] = true;
}

InputSystem::~InputSystem() {

}

void InputSystem::init() {

}

void InputSystem::update(float dt) {
	for (auto& e : m_entityArray) {
		if (!m_window->IsAnyKeyEvent()) {
			float intensity = parentScene->getComponent<InputComponent>(e).intensity;
			if (m_window->IsKeyPressed(GLFW_KEY_W)) {
				parentScene->getComponent<MotionComponent>(e).velocity.y = -intensity;
			}
			if (m_window->IsKeyPressed(GLFW_KEY_S)) {
				parentScene->getComponent<MotionComponent>(e).velocity.y = intensity;
			}
			if (m_window->IsKeyPressed(GLFW_KEY_A)) {
				parentScene->getComponent<MotionComponent>(e).velocity.x = -intensity;
			}
			if (m_window->IsKeyPressed(GLFW_KEY_D)) {
				parentScene->getComponent<MotionComponent>(e).velocity.x = intensity;
			}
		}
		else {
			parentScene->getComponent<MotionComponent>(e).velocity = glm::vec2(0.0f);
		}
	}
}
void InputSystem::draw() {
}