#pragma once

#include "Kikurage/ECS/System.h"

#include "Kikurage/Core/Renderer/EditorCamera.h"

namespace Kikurage {
	class CameraSystem : public System {
	private:
		EditorCamera camera;

	public:
		CameraSystem();
		~CameraSystem();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}
