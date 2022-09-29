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

	void Init() override;
	void Update(float dt) override;
	void Draw() override;

	void onCollisionEvent(CollisionEvent* collision);
};
