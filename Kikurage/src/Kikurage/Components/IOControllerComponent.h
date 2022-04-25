#pragma once

#include "Kikurage/ECS/Component.h"

class IOControllerComponent : public Component {
public:
	int fingerType = 0;

public:
	IOControllerComponent() {}
	IOControllerComponent(int type) : fingerType(type) {}
};