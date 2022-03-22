#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "ECS/ECS_def.h"

class Entity {
private:
	EntityID m_id;

public:
	Entity(EntityID id) : m_id(id) {}
	~Entity() = default;
	inline EntityID GetID() { return m_id; }
};
