#pragma once

#include <unordered_map>
#include <array>

#include "Nameko/Entity.h"
#include "Nameko/Archtype.h" 
#include "Nameko/IdGenerator.h"
#include "System.h"
#include "Kikurage/Components/Relationship.h"
#include "Kikurage/Components/Name/Name.h"

namespace Nameko {
	class System;

	class ECS {
	private:
		EntityManager* m_entityManager;
		std::unordered_map<ArcheID, Archetype*>  m_archetypes;
		std::array<ArcheID, MAX_ENTITIES> m_entityToArche;
		std::vector<std::unique_ptr<System>> m_systems;

	public:
		ECS() {
			m_entityManager = new EntityManager;
		}

		~ECS() {
			delete m_entityManager;
			for (auto& pair : m_archetypes) {
				delete pair.second;
			}
		}

		void AddSystem(std::unique_ptr<System> system) {
			system->SetECS(this);
			m_systems.emplace_back(std::move(system));
		}

		void Init() {
			for (auto& system : m_systems) {
				system->Init();
			}
		}

		void Update(float dt) {
			for (auto& system : m_systems) {
				system->Update(dt);
			}
		}

		void Draw() {
			for (auto& system : m_systems) {
				system->Draw();
			}
		}

		Entity CreateEntity() {
			auto entity = m_entityManager->CreateEntity();
			char name[64];
			sprintf_s(name, "Entity %d", entity);
			this->AddComponent<Kikurage::Name>(entity, Kikurage::Name(name));
			this->AddComponent<Kikurage::Relationship>(entity, Kikurage::Relationship());
			return entity;
		}

		void AddRelationship(Entity parent, Entity child) {
			this->GetComponent<Kikurage::Relationship>(child)->parent = parent;
			auto current = this->GetComponent<Kikurage::Relationship>(parent)->first;
			if (current) {
				auto last = current;
				while (current) {
					last = current;
					current = this->GetComponent<Kikurage::Relationship>(current)->next;
				}
				this->GetComponent<Kikurage::Relationship>(last)->next = child;
				this->GetComponent<Kikurage::Relationship>(child)->prev = last;
			}
			else {
				this->GetComponent<Kikurage::Relationship>(parent)->first = child;
			}
		}

		void DestoryEntity(Entity e) {
			m_entityManager->DestroyEntity(e);
			m_archetypes[m_entityToArche[e]]->RemoveComponents(e);
		}

		template<typename Component>
		void AddComponent(Entity e, Component&& component) {
			auto oldArcheID = m_entityToArche[e];
			auto newArcheID = oldArcheID | IdGenerator::GetArche<Component>();

			if (this->HasComponent<Component>(e)) {
				std::cout << "Entity already has the Component." << std::endl;
			}
			else {
				if (!m_archetypes.contains(newArcheID)) {
					m_archetypes[newArcheID] = new Archetype;
				}
				m_archetypes[newArcheID]->AddComponent<Component>(e, std::forward<Component>(component), m_archetypes[oldArcheID]);
				m_entityToArche[e] = newArcheID;
			}
		}

		template<typename Component>
		Component* GetComponent(Entity e) {
			if (this->HasComponent<Component>(e)) {
				auto archeID = m_entityToArche[e];
				return m_archetypes[archeID]->GetComponent<Component>(e);
			}
			else {
				std::cout << "Entity doesn't have the Component." << std::endl;
				return nullptr;
			}
		}

		template<typename Component>
		inline bool HasComponent(Entity e) {
			return m_entityToArche[e] & IdGenerator::GetFamily<Component>();
		}

		template<typename Component>
		void RemoveComponent(Entity e) {
			if (this->HasComponent<Component>(e)) {
				auto oldArcheID = m_entityToArche[e];
				auto newArcheID = oldArcheID & ~IdGenerator::GetArche<Component>();

				if (newArcheID != 0) {
					if (!m_archetypes.contains(newArcheID)) {
						m_archetypes[newArcheID] = new Archetype;
					}
					m_archetypes[oldArcheID]->RemoveComponent<Component>(e, m_archetypes[newArcheID]);
				}
				else {
					m_archetypes[oldArcheID]->RemoveComponents(e);
				}
				m_entityToArche[e] = newArcheID;
			}
			else {
				std::cout << "Entity doesn't have the Component." << std::endl;
			}
		}

		template<typename... Components>
		void Each(const std::function<void(Components&...)>&& lambda) {
			auto mask = IdGenerator::GetArche<Components...>();
			for (const auto& [archeID, archetype] : this->m_archetypes) {
				if ((archeID & mask) == mask) {
					archetype->Each<Components...>(std::forward<const std::function<void(Components&...)>>(lambda));
				}
			}
		}
	};
}