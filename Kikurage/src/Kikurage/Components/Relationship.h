#pragma once

#include "Nameko/Entity.h"

namespace Kikurage {
	struct Relationship {
		Nameko::Entity first{ Nameko::ENTITY_NULL };
		Nameko::Entity prev{ Nameko::ENTITY_NULL };
		Nameko::Entity next{ Nameko::ENTITY_NULL };
		Nameko::Entity parent{ Nameko::ENTITY_NULL };
	};
}
