#pragma once

#include "Utils/Math.h"

namespace Kikurage {
	struct CollisionPoints {
		Vector3 A;
		Vector3 B;
		Vector3 Normal;
		float Depth;
		bool HasCollision;
	};
}
