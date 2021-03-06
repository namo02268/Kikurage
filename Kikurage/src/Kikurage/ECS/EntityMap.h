#pragma once
#include <unordered_map>
#include <array>

#include "Kikurage/ECS/Entity.h"
#include "Kikurage/ECS/ECS_def.h"

class EntityMap {
private:
	std::array<ComponentInstance, MAX_ENTITIES> m_entityToInstance;
	std::array<EntityID, MAX_ENTITIES> m_instanceToEntity;

public:
	~EntityMap() = default;

	Entity getEntity(ComponentInstance i) { return m_instanceToEntity[i]; }
	ComponentInstance getInstance(Entity e) { return m_entityToInstance[e.GetID()]; }

	void add(Entity& e, ComponentInstance i) {
		m_entityToInstance[e.GetID()] = i;
		m_instanceToEntity[i] = e.GetID();
	}

	void update(Entity& e, ComponentInstance i) {
		m_entityToInstance[e.GetID()] = i;
		m_instanceToEntity[i] = e.GetID();
	}
};