#pragma once

#include <iostream>

#include "Kikurage/ECS/ComponentManager.h"
#include "Kikurage/ECS/EntityManager.h"
#include "Kikurage/ECS/ECS_def.h"
#include "Kikurage/ECS/System.h"
#include "Kikurage/Events/EventHandler.h"

#include "Kikurage/Components/Relationship.h"

class ECS {
private:
	// entity manager
	std::unique_ptr<EntityManager> m_entityManager = std::make_unique<EntityManager>();
	// entity array
	std::vector<Entity> m_allEntityArray;
	// ComponentMask
	std::unordered_map<EntityID, ComponentFamily> m_componentMask;
	// bit array of component managers ID
	ComponentFamily m_componentFamily;
	// array of component managers
	std::array<std::unique_ptr<BaseComponentManager>, MAX_COMPONENTS_FAMILY> m_componentManagers;
	// systems
	std::vector<std::unique_ptr<System>> m_systems;

public:
	ECS(){};
	ECS(const ECS&) = delete;
	ECS& operator=(const ECS&) = delete;
	~ECS() = default;

	//---------------------------------------------Entity---------------------------------------------//
	Entity CreateEntity() {
		Entity e = m_entityManager->createEntity();
		m_allEntityArray.emplace_back(e);
		AddComponent<Relationship>(e, Relationship());
		return e;
	}

	void DestroyEntity(Entity e) {
		for (auto itr = m_allEntityArray.begin(); itr != m_allEntityArray.end(); ++itr) {
			Entity e_itr = *itr;
			if (e_itr == e) {
				m_allEntityArray.erase(itr);
				return;
			}
		}

		for (auto& system : m_systems) {
			system->RemoveEntity(e);
		}
		m_entityManager->destroyEnitity(e);
	}

	std::vector<Entity>& GetAllEntityArray() {
		return m_allEntityArray;
	}

	//---------------------------------------------System---------------------------------------------//
	void AddSystem(std::unique_ptr<System> system) {
		system->m_parentScene = this;
		m_systems.push_back(std::move(system));
	}

	void Init() {
		for (const auto& system : m_systems)
			system->Init();
	}

	void Update(float dt) {
		for (const auto& system : m_systems)
			system->Update(dt);
	}

	void Draw() {
		for (const auto& system : m_systems)
			system->Draw();
	}

	//---------------------------------------------Component---------------------------------------------//
	template<typename ComponentType>
	void AddComponent(Entity& e, ComponentType&& c) {
		auto family = getComponentTypeID<ComponentType>();
		if (!m_componentMask[e][family]) {
			m_componentMask[e][family] = true;


			// if the component manager didn't exists
			if (!m_componentFamily[family]) {
				m_componentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
				m_componentFamily[family] = true;
			}

			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).addComponent(e, std::forward<ComponentType>(c));
			UpdateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " is already attached! Entity ID:" << e << std::endl;
		}
	}

	template<typename ComponentType>
	void RemoveComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		if (m_componentMask[e][family]) {
			m_componentMask[e][family] = false;
			static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).removeComponent(e);
			UpdateComponentMap(e, family);
		}
		else {
			std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e << std::endl;
		}
	}

	template<typename ComponentType>
	ComponentType* GetComponent(Entity& e) {
		auto family = getComponentTypeID<ComponentType>();
		if (m_componentMask[e][family]) {
			return static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).getComponent(e);
		}
		else {
			std::cout << typeid(ComponentType).name() << " does not exist! Entity ID:" << e << std::endl;
			return nullptr;
		}
	}

	template<typename ComponentType>
	void IterateAll(std::function<void(ComponentType* c)> lambda) {
		auto family = getComponentTypeID<ComponentType>();
		static_cast<ComponentManager<ComponentType>&>(*m_componentManagers[family]).iterateAll(lambda);
	}

	ComponentFamily GetComponentMask(Entity& e) {
		return m_componentMask[e];
	}

private:
	void UpdateComponentMap(Entity& e, ComponentTypeID family) {
		for (const auto& system : m_systems) {
			auto& componentMap = m_componentMask[e];
			auto requiredComponent = system->m_requiredComponent;
			if (requiredComponent[family]) {
				auto andbit = requiredComponent & componentMap;
				if (andbit == system->m_requiredComponent) {
					system->AddEntity(e);
				}
				else {
					system->RemoveEntity(e);
				}

			}
		}
	}
};