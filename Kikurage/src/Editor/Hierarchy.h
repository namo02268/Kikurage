#pragma once

#include "imgui/imgui.h"
#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/Relationship.h"
#include "Kikurage/Components/Name/Name.h"

namespace Kikurage {
	Entity Hierarchy(ECS* ecs) {
		auto& allEntity = ecs->GetAllEntityArray();
		static EntityID selectedEntity = ENTITY_NULL;

		ImGui::Begin("Hierarchy");
		ImGui::PushID("Hierarchy");
		ImGui::Indent();

		for (int n = 0; n < allEntity.size(); n++) {
			auto currentEntity = allEntity[n];
			if (!ecs->GetComponent<Relationship>(currentEntity)->parent) {
				auto& name = ecs->GetComponent<Name>(currentEntity)->GetName();
				auto nextEntity = ecs->GetComponent<Relationship>(currentEntity)->first;
				if (nextEntity != ENTITY_NULL) {
					ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
					ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
					if(selectedEntity == currentEntity) node_flags |= ImGuiTreeNodeFlags_Selected;
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)currentEntity, node_flags, name.c_str());
					if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
						selectedEntity = currentEntity;
					if (node_open) {
						if (ImGui::IsItemClicked()) {
							selectedEntity = currentEntity;
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
					if (ImGui::Selectable(name.c_str(), selectedEntity == currentEntity)) {
						selectedEntity = currentEntity;
					}
				}
			}
		}
		ImGui::PopID();
		ImGui::End();

		return selectedEntity;
	}
}
