#pragma once

#include "Nameko/ECS.h"
#include "Kikurage/Components/Relationship.h"
#include "Kikurage/Components/Name/Name.h"

namespace Kikurage {
	class KikurageECS : public Nameko::ECS {
	public:
		KikurageECS() = default;
		~KikurageECS() = default;

		Nameko::Entity CreateEntity() override {
			auto entity = m_entityManager->CreateEntity();
			char name[64];
			sprintf_s(name, "Entity %d", entity);
			this->AddComponent<Kikurage::Name>(entity, Kikurage::Name(name));
			this->AddComponent<Kikurage::Relationship>(entity, Kikurage::Relationship());
			return entity;
		}

		void AddRelationship(Nameko::Entity parent, Nameko::Entity child) {
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

	};
}
