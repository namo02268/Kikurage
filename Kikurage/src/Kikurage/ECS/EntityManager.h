#pragma once

#include "Kikurage/ECS/Entity.h"
#include "Kikurage/ECS/IdGenerator.h"

namespace Kikurage {
	class EntityManager {
	public:
		Entity createEntity() { return Entity(getEntityID()); }
		void destroyEnitity(Entity e) {}
	};
}
