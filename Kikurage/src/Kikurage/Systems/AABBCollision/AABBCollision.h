#pragma once

#include "Kikurage/ECS/System.h"

#include "Kikurage/Resource/Mesh/AABB.h"

class AABBCollision : public System {
private:

public:
	AABBCollision();
	~AABBCollision();

	void init() override;
	void update(float dt) override;
	void draw() override;

private:
	bool intersect(AABB& a, AABB& b);
};
