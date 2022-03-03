#pragma once

#include "Component.h"
class PlayerComponent : public Component {
public:
	float walkspeed = 3.0f;

	PlayerComponent() {}
	PlayerComponent(float walkspeed) : walkspeed(walkspeed) {}
};