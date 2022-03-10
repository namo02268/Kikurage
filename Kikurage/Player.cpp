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
	m_eventHandler->subscribe(this, &Player::OnCollisionEvent);
}

void Player::update(float dt) {
	for (auto& e : m_entityArray) {
		auto& motionComponent = m_parentScene->getComponent<MotionComponent>(e);
		if (!m_window->IsAnyKeyEvent()) {
			float walkspeed = m_parentScene->getComponent<PlayerComponent>(e).walkspeed;
			auto& spriteComponent = m_parentScene->getComponent<SpriteComponent>(e);

			if (m_window->IsKeyPressed(GLFW_KEY_W)) {
				motionComponent.velocity.y = -walkspeed;
				spriteComponent.UVoffset = 11;
			}
			else if (m_window->IsKeyPressed(GLFW_KEY_S)) {
				motionComponent.velocity.y = walkspeed;
				spriteComponent.UVoffset = 2;
			}
			else if (m_window->IsKeyPressed(GLFW_KEY_A)) {
				motionComponent.velocity.x = -walkspeed;
				spriteComponent.UVoffset = 5;
			}
			else if (m_window->IsKeyPressed(GLFW_KEY_D)) {
				motionComponent.velocity.x = walkspeed;
				spriteComponent.UVoffset = 8;
			}
		}
		else {
			motionComponent.velocity = glm::vec2(0.0f);
		}
	}
}
void Player::draw() {
}

void Player::OnCollisionEvent(CollisionEvent* collision) {
	auto& a_Trans = m_parentScene->getComponent<TransformComponent>(collision->a);
	auto& b_Trans = m_parentScene->getComponent<TransformComponent>(collision->b);

	if (m_window->IsKeyPressed(GLFW_KEY_W)) {
		a_Trans.position.y = b_Trans.position.y + b_Trans.size.y * 1.01;
	}
	else if (m_window->IsKeyPressed(GLFW_KEY_S)) {
		a_Trans.position.y = b_Trans.position.y - b_Trans.size.y * 1.01;
	}
	else if (m_window->IsKeyPressed(GLFW_KEY_A)) {
		a_Trans.position.x = b_Trans.position.x + b_Trans.size.x * 1.01;
	}
	else if (m_window->IsKeyPressed(GLFW_KEY_D)) {
		a_Trans.position.x = b_Trans.position.x - b_Trans.size.x * 1.01;
	}
}