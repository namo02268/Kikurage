#pragma once

#include "System.h"

class ColliderSystem : public System {
public:
	ColliderSystem();
	~ColliderSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};