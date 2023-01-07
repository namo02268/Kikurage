#pragma once

#include "Kikurage/ECS/System.h"

namespace Kikurage {
	class TransformUpdater : public System {
	public:
		TransformUpdater();
		~TransformUpdater();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;

	};
}