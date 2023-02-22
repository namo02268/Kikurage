#pragma once

#include "Kikurage/Core/ECS/ECS.h"

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