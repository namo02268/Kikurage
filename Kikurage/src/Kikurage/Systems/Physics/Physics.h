#pragma once

#include "Utils/Math.h"
#include "Kikurage/ECS/System.h"
#include "Kikurage/Events/CollisionEvent.h"

namespace Kikurage {
	class Physics : public System {
	private:
		Vector3 m_gravity{ 0.0f, -9.81f, 0.0f };

	public:
		Physics();
		~Physics();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;

		void onCollisionEvent(CollisionEvent* collision);
	};
}
