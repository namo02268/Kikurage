#pragma once

#include "Nameko/ECS.h"

namespace Kikurage {
	class Lighting : public Nameko::System {
	public:
		Lighting();
		~Lighting();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}
