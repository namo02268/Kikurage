#pragma once
#include <array>

#include "Kikurage/ECS/Entity.h"
#include "Kikurage/ECS/ECS_def.h"

class SparseSet {
private:
	std::array<EntityID, MAX_ENTITIES> m_sparse;
	std::array<ComponentInstance, MAX_COMPONENTS> m_dense;

public:
	~SparseSet() = default;

	Entity getEntity(ComponentInstance i) { return m_sparse[i]; }
	ComponentInstance getInstance(Entity e) { return m_dense[e]; }

	void Add(Entity& e, ComponentInstance i) {
		m_dense[e] = i;
		m_sparse[i] = e;
	}

	void Update(Entity& e, ComponentInstance i) {
		m_dense[e] = i;
		m_sparse[i] = e;
	}
};