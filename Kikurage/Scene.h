#pragma once

#include <iostream>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "ECS_def.h"
#include "System.h"
#include "EventHandler.h"

class Scene {
private:
	// entity manager
	std::unique_ptr<EntityManager> m_entityManager;
	// event handler
	std::unique_ptr<EventHandler> m_eventHandler;
	// bit array of component managers ID
	ComponentFamily m_componentFamily;
	// array of component managers
	std::array<std::unique_ptr<BaseComponentManager>, MAX_COMPONENTS_FAMILY> m_componentManagers;
	// systems
	std::vector<std::unique_ptr<System>> m_systems;

public:
	explicit Scene(std::unique_ptr<EntityManager> entityManager, std::unique_ptr<EventHandler> eventHandler)
		: m_entityManager(std::move(entityManager)), m_eventHandler(std::move(eventHandler)) {};

	//---------------------------------------------Entity---------------------------------------------//
	Entity createEntity() { return m_entityManager->createEntity(); }

	void destroyEntity(Entity e) {
		for (auto& system : m_systems) {
			system->removeEntity(e);
		}
		m_entityManager->destroyEnitity(e);
	}

	//---------------------------------------------System---------------------------------------------//
	void addSystem(std::unique_ptr<System> system) {
		system->m_parentScene = this;
		system->m_eventHandler = m_eventHandler.get();
		m_systems.push_back(std::move(system));
	}

	void init() {
		for (const auto& system : m_systems)
			system->init();
	}

	void update(float dt) {
		for (const auto& system : m_systems)
			system->update(dt);
	}

	void draw() {
		for (const auto& system : m_systems)
			system->draw();
	}

	//---------------------------------------------Component---------------------------------------------//
	template<typename ComponentType, typename... TArgs>
	void addComponent(Entity& e, TArgs&&... mArgs) {
		auto family = getComponentTypeID<ComponentType>();
		if (!e.attachedComponent[family]) {
			e.attachedComponent[family] = true;

			// if the component manager didn't exists
			if (!m_componentFamily[family]) {
				m_componentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
				m_componentFamily[family] = true;
			}

			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).addComponent(e, std::forward<TArgs>(mArgs)...);
			updateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " is already attached! Entity ID:" << e.GetID() << std::endl;
		}
	}

	template<typename ComponentType>
	void removeComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		if (e.attachedComponent[family]) {
			e.attachedComponent[family] = false;
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).removeComponent(e);
			updateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e.GetID() << std::endl;
		}
	}

	// TODO : [Add] error handling
	template<typename ComponentType>
	ComponentType& getComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
	}

	void updateComponentMap(Entity& e, ComponentTypeID family) {
		for (const auto& system : m_systems) {
			auto componentMap = e.attachedComponent;
			auto requiredComponent = system->m_requiredComponent;
			if (requiredComponent[family]) {
				auto andbit = requiredComponent & componentMap;
				if (andbit == system->m_requiredComponent) {
					system->addEntity(e);
				}
				else {
					system->removeEntity(e);
				}

			}
		}
	}
};