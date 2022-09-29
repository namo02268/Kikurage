#pragma once

#include "Kikurage/ECS/System.h"

#include "Kikurage/Resource/Mesh/AABB.h"

class AABBCollision : public System {
private:

public:
	AABBCollision();
	~AABBCollision();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;

private:
	bool intersect(AABB& a, AABB& b);
};
