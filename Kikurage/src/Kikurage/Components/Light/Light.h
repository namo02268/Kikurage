#pragma once

#include "Utils/Math.h"

namespace Kikurage {
	struct Light
	{
		Vector3 color{ 1.0f };
		float linear = 0.7f;
		float quadratic = 1.8f;

		Light() {}
		Light(Vector3 color, float linear = 0.9f, float quadratic = 0.01f) :
			color(color),
			linear(linear),
			quadratic(quadratic)
		{}
	};
}