#pragma once
#include "ECS/System.h"

class CollisionSystem : public System {
private:

public:
	CollisionSystem();
	~CollisionSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};
