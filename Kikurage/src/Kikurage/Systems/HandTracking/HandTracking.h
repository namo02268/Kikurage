#pragma once

#include <glm/glm.hpp>

#include "Kikurage/ECS/System.h"
#include "Leap/LeapC++.h"

class HandTracking : public System {
private:
	Leap::Controller controller;
	glm::vec3 indexFinger = glm::vec3(0.0f);

public:
	HandTracking();
	~HandTracking();

	void init() override;
	void update(float dt) override;
	void draw() override;
};
