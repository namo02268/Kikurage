#pragma once

#include "Component.h"
class InputComponent : public Component {
public:
	float intensity = 3.0f;

	InputComponent() {}
	InputComponent(float intensity) : intensity(intensity) {}
};