#pragma once

#include "Kikurage/ECS/System.h"

class TransformUpdator : public System {
public:
	TransformUpdator();
	~TransformUpdator() = default;

	void init() override;
	void update(float dt) override;
	void draw() override;
};