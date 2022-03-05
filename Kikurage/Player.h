#pragma once

#include "System.h"
#include "Window.h"

#include "CollisionEvent.h"

class Player : public System {
private:
	Window* m_window;
	float m_walkMotionCount = 0;

public:
	Player(Window* window);
	~Player();

	void init() override;
	void update(float dt) override;
	void draw() override;

	void OnCollisionEvent(CollisionEvent* collision);
};