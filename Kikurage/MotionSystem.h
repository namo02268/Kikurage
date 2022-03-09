#pragma once

#include "System.h"

class MotionSystem : public System {
private:

public:
	MotionSystem();
	~MotionSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};