#pragma once

#include "imgui/imgui.h"
#include "Kikurage/Core/ECS/ECS.h"
#include "Editor/ComponentEditors.h"

namespace Kikurage {
	void Inspector(Nameko::Entity entity, KikurageECS* ecs) {

		ImGui::Begin("Inspector");
		ImGui::PushID("Inspector");

		if (entity != Nameko::ENTITY_NULL) {
			// Transform
			if (ecs->HasComponent<Transform>(entity)) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				TransformEditor(entity, ecs);
				ImGui::Separator();
			}

			// Camera
			if (ecs->HasComponent<Camera>(entity)) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				CameraEditor(entity, ecs);
				ImGui::Separator();
			}

			if (ecs->HasComponent<Light>(entity)) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				LightEditor(entity, ecs);
				ImGui::Separator();
			}

			// Material
			if (ecs->HasComponent<Material>(entity)) {
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
					ecs->AddComponent<Material>(entity, Material());
				ImGui::EndPopup();
			}
			ImGui::PopItemWidth();
			ImGui::PopID();

			ImGui::End();
		}
	}
}