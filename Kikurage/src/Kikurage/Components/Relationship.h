#pragma once

#include "Kikurage/ECS/Component.h"
#include "Kikurage/ECS/Entity.h"

namespace Kikurage {
	struct Relationship : public Component {
		Entity parent{};
	};
}
