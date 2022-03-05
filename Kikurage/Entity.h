#pragma once

#include "ECS_def.h"

class Entity {
private:
	EntityID m_id;
public:
	ComponentFamily m_componentMap;

public:
	Entity(EntityID id) : m_id(id) {}
	EntityID GetID() { return m_id; }
};