#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "ECS_def.h"

class Entity {
private:
	EntityID m_id;
public:
	ComponentFamily attachedComponent;
	std::string name;

public:
	Entity(EntityID id) : m_id(id) {
		std::ostringstream ss;
		ss << "Entity " << std::setfill('0') << std::right << std::setw(4) << id;
		name = ss.str();
	}
	EntityID GetID() { return m_id; }
};