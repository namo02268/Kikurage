#pragma once
#include <glm/glm.hpp>
#include "Kikurage/ECS/System.h"

#include "Kikurage/Events/CollisionEvent.h"

class Physics : public System {
private:
	glm::vec3 m_gravity = glm::vec3(0, -9.81f, 0);

public:
	Physics();
	~Physics();

	void init() override;
	void update(float dt) override;
	void draw() override;

	void onCollisionEvent(CollisionEvent* collision);
};
