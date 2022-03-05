#pragma once

#include "EntityMap.h"

class BaseComponentManager {
public:
	virtual ~BaseComponentManager() {}
};

template<typename ComponentType>
class ComponentManager : public BaseComponentManager {
private:
	std::array<std::unique_ptr<ComponentType>, MAX_COMPONENTS_ARRRAY> m_componentArray;
	EntityMap m_entityMap;
	ComponentInstance m_newInstance = 0;

public:
	template<typename... TArgs>
	void addComponent(Entity& e, TArgs&&... mArgs) {
		ComponentType* c = new ComponentType(std::forward<TArgs>(mArgs)...);
		std::unique_ptr<ComponentType> uPtr(c);
		m_componentArray[m_newInstance] = std::move(uPtr);
		m_entityMap.add(e, m_newInstance);

		m_newInstance++;
	}

	ComponentType& getComponent(Entity& e) {
		ComponentInstance instance = m_entityMap.getInstance(e);
		return *m_componentArray[instance];
	}

	void removeComponent(Entity& e) {
		ComponentInstance instance = m_entityMap.getInstance(e);
		ComponentInstance lastInstance = m_newInstance - 1;
		Entity lastEntity = m_entityMap.getEntity(lastInstance);

		m_entityMap.remove(e);

		if (instance != lastInstance) {
			m_componentArray[instance] = std::move(m_componentArray[lastInstance]);
			m_entityMap.update(lastEntity, instance);
		}

		m_newInstance--;
	}
};