#pragma once

#include <iostream>

#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/ECS_def.h"
#include "ECS/System.h"
#include "ECS/EventHandler.h"

class Scene {
private:
	// entity manager
	std::unique_ptr<EntityManager> m_entityManager;
	// entity array
	std::vector<Entity> m_allEntityArray;
	// event handler
	std::unique_ptr<EventHandler> m_eventHandler;
	// ComponentMask
	std::unordered_map<EntityID, ComponentFamily> m_componentMask;
	// bit array of component managers ID
	ComponentFamily m_componentFamily;
	// array of component managers
	std::array<std::unique_ptr<BaseComponentManager>, MAX_COMPONENTS_FAMILY> m_componentManagers;
	// systems
	std::vector<std::unique_ptr<System>> m_systems;

public:
	Scene(std::unique_ptr<EntityManager> entityManager, std::unique_ptr<EventHandler> eventHandler)
		: m_entityManager(std::move(entityManager)), m_eventHandler(std::move(eventHandler)) {};
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	~Scene() = default;

	//---------------------------------------------Entity---------------------------------------------//
	Entity createEntity() {
		Entity e = m_entityManager->createEntity();
		m_allEntityArray.emplace_back(e); 
		return e;
	}

	void destroyEntity(Entity e) {
		for (auto itr = m_allEntityArray.begin(); itr != m_allEntityArray.end(); ++itr) {
			Entity e_itr = *itr;
			if (e_itr.GetID() == e.GetID()) {
				m_allEntityArray.erase(itr);
				return;
			}
		}

		for (auto& system : m_systems) {
			system->removeEntity(e);
		}
		m_entityManager->destroyEnitity(e);
	}

	std::vector<Entity>& getAllEntityArray() {
		return m_allEntityArray;
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
		if (!m_componentMask[e.GetID()][family]) {
			m_componentMask[e.GetID()][family] = true;


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
		if (m_componentMask[e.GetID()][family]) {
			m_componentMask[e.GetID()][family] = false;
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).removeComponent(e);
			updateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e.GetID() << std::endl;
		}
	}

	// TODO : [Add] error handling
	template<typename ComponentType>
	ComponentType* getComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		if (m_componentMask[e.GetID()][family]) {
			return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
		}
		else {
			std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e.GetID() << std::endl;
			return nullptr;
		}
	}

	ComponentFamily getComponentMask(Entity& e) {
		return m_componentMask[e.GetID()];
	}

private:
	void updateComponentMap(Entity& e, ComponentTypeID family) {
		for (const auto& system : m_systems) {
			auto& componentMap = m_componentMask[e.GetID()];
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