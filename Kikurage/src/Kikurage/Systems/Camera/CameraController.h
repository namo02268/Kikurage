#pragma once

#include "Kikurage/Core/Renderer/EditorCamera.h"
#include "Nameko/ECS.h"

namespace Kikurage {
	class CameraController : public Nameko::System {
	private:
		EditorCamera camera;

	public:
		CameraController();
		~CameraController();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}
