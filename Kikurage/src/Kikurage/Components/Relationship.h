#pragma once

#include "Kikurage/ECS/Component.h"
#include "Kikurage/ECS/Entity.h"

namespace Kikurage {
	struct Relationship : public Component {
		Entity first{ ENTITY_NULL };
		Entity prev{ ENTITY_NULL };
		Entity next{ ENTITY_NULL };
		Entity parent{ ENTITY_NULL };
	};
}
