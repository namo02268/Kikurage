#pragma once

#include "Nameko/ECS.h"

namespace Kikurage {
	class TransformUpdater : public Nameko::System {
	public:
		TransformUpdater();
		~TransformUpdater();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;

	};
}