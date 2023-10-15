#pragma once

#include "imgui/imgui.h"
#include "Kikurage/Core/ECS/ECS.h"
#include "Kikurage/Components/Relationship/Relationship.h"
#include "Kikurage/Components/Name/Name.h"

namespace Kikurage {
	Nameko::Entity Hierarchy(Nameko::ECS* ecs) {
		static Nameko::Entity selectedEntity = Nameko::ENTITY_NULL;

		ImGui::Begin("Hierarchy");
		ImGui::PushID("Hierarchy");
		ImGui::Indent();

		ecs->EachEntity<Name, Relationship>([&](Nameko::Entity& entity) {
			if (!ecs->GetComponent<Relationship>(entity)->parent) {
				auto& name = ecs->GetComponent<Name>(entity)->GetName();
				auto nextEntity = ecs->GetComponent<Relationship>(entity)->first;
				if (nextEntity != Nameko::ENTITY_NULL) {
//					ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
					ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
					if (selectedEntity == entity) node_flags |= ImGuiTreeNodeFlags_Selected;
					ImGui::PushID(entity);
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)entity, node_flags, name.c_str());
					ImGui::PopID();
					if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
						selectedEntity = entity;
					if (node_open) {
						if (ImGui::IsItemClicked()) {
							selectedEntity = entity;
						}
						ImGui::Indent();
						while (nextEntity) {
							auto& childname = ecs->GetComponent<Name>(nextEntity)->GetName();
							if (ImGui::Selectable(childname.c_str(), selectedEntity == nextEntity)) {
								selectedEntity = nextEntity;
							}
							nextEntity = ecs->GetComponent<Relationship>(nextEntity)->next;
						}
						ImGui::TreePop();
					}
				}
				else {
					if (ImGui::Selectable(name.c_str(), selectedEntity == entity)) {
						selectedEntity = entity;
					}
				}
			}
		});

		ImGui::PopID();
		ImGui::End();

		return selectedEntity;
	}
}
