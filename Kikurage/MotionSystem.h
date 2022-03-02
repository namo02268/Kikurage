#pragma once

#include "System.h"

class MotionSystem : public System {
public:
	MotionSystem();
	~MotionSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};