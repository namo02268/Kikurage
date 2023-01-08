#pragma once

#include "Kikurage/ECS/System.h"

#include "Kikurage/Core/Renderer/EditorCamera.h"

namespace Kikurage {
	class CameraController : public System {
	private:
		EditorCamera camera;

	public:
		CameraController();
		~CameraController();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;

	private:
		void HandleMouse(Transform& transform, float dt);
		void HandleKeyboard(Transform& transform, float dt);
		void HandleScroll(Transform& transform, float dt);
	};
}
