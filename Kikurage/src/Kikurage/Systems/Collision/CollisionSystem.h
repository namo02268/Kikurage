#pragma once
#include "Kikurage/ECS/System.h"

namespace Kikurage {
	class CollisionSystem : public System {
	private:

	public:
		CollisionSystem();
		~CollisionSystem();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}
