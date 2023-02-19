#pragma once

#include "Kikurage/Resource/Mesh/AABB.h"

namespace Kikurage {
	class AABBCollision {
	private:

	public:
		AABBCollision();
		~AABBCollision();

		void Init();
		void Update(float dt);
		void Draw();

	private:
		bool intersect(AABB& a, AABB& b);
	};
}
