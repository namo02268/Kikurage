#pragma once
#include <unordered_map>
#include <array>

#include "Entity.h"
#include "ECS_def.h"

class EntityMap {
private:
	std::unordered_map<EntityID, ComponentInstance> m_entityToInstance;
	std::array<EntityID, MAX_COMPONENTS_ARRRAY> m_instanceToEntity;

public:
	Entity getEntity(ComponentInstance i) { return m_instanceToEntity[i]; }
	ComponentInstance getInstance(Entity e) { return m_entityToInstance[e.GetID()]; }

	void add(Entity& e, ComponentInstance i) {
		m_entityToInstance.insert({ e.GetID(), i });
		m_instanceToEntity[i] = e.GetID();
	}

	void update(Entity& e, ComponentInstance i) {
		m_entityToInstance[e.GetID()] = i;
		m_instanceToEntity[i] = e.GetID();
	}
	void remove(Entity& e) { m_entityToInstance.erase(e.GetID()); }
};