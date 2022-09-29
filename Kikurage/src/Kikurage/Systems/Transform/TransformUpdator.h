#pragma once

#include "Kikurage/ECS/System.h"

class TransformUpdator : public System {
public:
	TransformUpdator();
	~TransformUpdator() = default;

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
};