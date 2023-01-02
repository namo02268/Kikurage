#pragma once

#include <vector>

#include "Kikurage/ECS/Entity.h"
#include "Kikurage/ECS/ECS_def.h"
#include "Kikurage/Events/EventHandler.h"

namespace Kikurage {
	class ECS;

	class System {
	protected:
		std::vector<Entity> m_entityArray;

	public:
		ECS* m_parentScene;
		ComponentFamily m_requiredComponent;

	public:
		virtual ~System() {}

		virtual void Init() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw() = 0;

		void AddEntity(Entity& e) {
			m_entityArray.emplace_back(e);
		}

		void RemoveEntity(Entity& e) {
			for (auto itr = m_entityArray.begin(); itr != m_entityArray.end(); ++itr) {
				Entity e_itr = *itr;
				if (e_itr == e) {
					m_entityArray.erase(itr);
					return;
				}
			}
		}
	};
}
