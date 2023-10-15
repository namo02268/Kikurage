#pragma once

#include "Nameko/ECS.h"

namespace Kikurage {
	class MeshRenderer : public Nameko::System {
	public:
		MeshRenderer();
		~MeshRenderer();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}
