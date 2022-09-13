#pragma once

#include <glm/glm.hpp>
#include "Kikurage/Core/Renderer/BaseCamera.h"


class EditorCamera : public BaseCamera {
public:
	EditorCamera() {}
	~EditorCamera() {}

	virtual void HandleMouse(TransformComponent& transform, float dt) override;
	virtual void HandleKeyboard(TransformComponent& transform, float dt) override;
	virtual void HandleScroll(TransformComponent& transform, float offset, float dt) override;
};