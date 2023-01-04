#pragma once

#include <glm/glm.hpp>
#include "Kikurage/Core/Renderer/BaseCamera.h"

namespace Kikurage {
	class EditorCamera : public BaseCamera {
	public:
		EditorCamera() {}
		~EditorCamera() {}

		virtual void HandleMouse(Transform& transform, float dt) override;
		virtual void HandleKeyboard(Transform& transform, float dt) override;
		virtual void HandleScroll(Transform& transform, float offset, float dt) override;
	};
}
