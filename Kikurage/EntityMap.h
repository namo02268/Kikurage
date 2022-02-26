#pragma once
#include <map>
#include <array>

#include "Entity.h"
#include "Defs.h"

class EntityMap {
private:
	std::map<EntityID, ComponentInstance> entityToInstance;
	std::array<EntityID, MAX_COMPONENTS_ARRRAY> instanceToEntity;

public:
	Entity getEntity(ComponentInstance i) { return instanceToEntity[i]; }
	ComponentInstance getInstance(Entity e) { return entityToInstance[e.GetID()]; }

	void add(Entity& e, ComponentInstance i) {
		entityToInstance.insert({ e.GetID(), i });
		instanceToEntity[i] = e.GetID();
	}

	void update(Entity& e, ComponentInstance i) {
		entityToInstance[e.GetID()] = i;
		instanceToEntity[i] = e.GetID();
	}
	void remove(Entity& e) { entityToInstance.erase(e.GetID()); }
};