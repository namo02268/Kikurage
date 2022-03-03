#include "Player.h"
#include "Scene.h"

#include "TransformComponent.h"
#include "MotionComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"

Player::Player(Window* window) {
	this->m_window = window;
	// Transform
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	// Motion
	family = getComponentTypeID<MotionComponent>();
	m_requiredComponent[family] = true;
	// Input
	family = getComponentTypeID<PlayerComponent>();
	m_requiredComponent[family] = true;
	// Sprite
	family = getComponentTypeID<SpriteComponent>();
	m_requiredComponent[family] = true;
}

Player::~Player() {

}

void Player::init() {

}

void Player::update(float dt) {
	for (auto& e : m_entityArray) {
		auto& motionComponent = m_parentScene->getComponent<MotionComponent>(e);
		if (!m_window->IsAnyKeyEvent()) {
			float walkspeed = m_parentScene->getComponent<PlayerComponent>(e).walkspeed;
			auto& spriteComponent = m_parentScene->getComponent<SpriteComponent>(e);
			m_walkMotionCount += dt;

			if (m_window->IsKeyPressed(GLFW_KEY_W)) {
				motionComponent.velocity.y = -walkspeed;
				if(m_walkMotionCount > 1)
				spriteComponent.UVoffset = 11;
			}
			if (m_window->IsKeyPressed(GLFW_KEY_S)) {
				motionComponent.velocity.y = walkspeed;
				spriteComponent.UVoffset = 2;
			}
			if (m_window->IsKeyPressed(GLFW_KEY_A)) {
				motionComponent.velocity.x = -walkspeed;
				spriteComponent.UVoffset = 5;
			}
			if (m_window->IsKeyPressed(GLFW_KEY_D)) {
				motionComponent.velocity.x = walkspeed;
				spriteComponent.UVoffset = 8;
			}
		}
		else {
			m_walkMotionCount = 0.0f;
			motionComponent.velocity = glm::vec2(0.0f);
		}
	}
}
void Player::draw() {
}