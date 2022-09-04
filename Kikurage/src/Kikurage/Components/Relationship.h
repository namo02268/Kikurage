#pragma once

#include "Kikurage/ECS/Component.h"
#include "Kikurage/ECS/Entity.h"

struct Relationship : public Component {
	Entity parent{};
};