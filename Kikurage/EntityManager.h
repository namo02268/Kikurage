#pragma once

#include "Entity.h"
#include "IdGenerator.h"

class EntityManager {
public:
	Entity createEntity() { return Entity(getEntityID()); }
};