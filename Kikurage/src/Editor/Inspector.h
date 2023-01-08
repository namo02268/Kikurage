#pragma once

#include "imgui/imgui.h"
#include "Kikurage/ECS/ECS.h"
#include "Editor/ComponentEditors.h"

namespace Kikurage {
	void Inspector(Entity entity, ECS* ecs) {
		ImGui::Begin("Inspector");
		ImGui::PushID("Inspector");

		if (entity != ENTITY_NULL) {
			// Transform
			auto typeID = getComponentTypeID<Transform>();
			if (ecs->GetComponentMask(entity)[typeID]) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				TransformEditor(entity, ecs);
				ImGui::Separator();
			}

			// Material
			typeID = getComponentTypeID<MaterialComponent>();
			if (ecs->GetComponentMask(entity)[typeID]) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				MaterialEditor(entity, ecs);
				ImGui::Separator();
			}

			// Add Component
			ImGui::PushItemWidth(50.0f);
			if (ImGui::Button("Add Component")) {
				ImGui::OpenPopup("Component");
			}

			if (ImGui::BeginPopup("Component"))
			{
				if (ImGui::Selectable("Transform"))
					ecs->AddComponent<Transform>(entity, Transform());
				if (ImGui::Selectable("Material"))
					ecs->AddComponent<MaterialComponent>(entity, MaterialComponent());
				ImGui::EndPopup();
			}
			ImGui::PopItemWidth();
			ImGui::PopID();

			ImGui::End();
		}
	}
}