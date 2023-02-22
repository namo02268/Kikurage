#pragma once

#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Camera/Camera.h"
#include "Kikurage/Core/ECS/ECS.h"

namespace Kikurage {
	class CameraController : public Nameko::System {
	private:
		Vector2 m_prevCursorPos{ 0.0f };

	public:
		CameraController();
		~CameraController();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;

	private:
		void HandleMouse(Transform& transform, Camera& camera, float dt);
		void HandleKeyboard(Transform& transform, Camera& camera, float dt);
		void HandleScroll(Transform& transform, Camera& camera, float offset, float dt);
	};
}
