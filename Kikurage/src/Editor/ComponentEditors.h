#pragma once
#include "Kikurage/ECS/ECS.h"
#include "imgui/imgui.h"

#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/MaterialComponent.h"

namespace Kikurage {
	void TransformEditor(Entity entity, ECS* ecs) {
		if (ImGui::TreeNode("Transform")) {
			auto transform = ecs->GetComponent<Transform>(entity);
			auto position = transform->GetPosition();
			auto rotation = transform->GetRotation();
			auto scale = transform->GetScale();
			if (ImGui::DragFloat3("Position", &position[0], 0.01f)) { transform->SetPosition(position); }
			if (ImGui::DragFloat3("Rotation", &rotation[0], 1.0f)) { transform->SetRotation(rotation); }
			if (ImGui::DragFloat3("Scale", &scale[0], 0.01f)) { transform->SetScale(scale); }

			if (ImGui::Button("Remove Component"))
				ecs->RemoveComponent<Transform>(entity);
			ImGui::TreePop();
		}
	}

	void MaterialEditor(Entity entity, ECS* ecs) {
		if (ImGui::TreeNode("Material")) {
			auto materialComponent = ecs->GetComponent<MaterialComponent>(entity);
			ImGui::ColorEdit3("Albedo", &materialComponent->albedo.x);
			ImGui::SliderFloat("Metallic", &materialComponent->metallic, 0.0f, 1.0f);
			ImGui::SliderFloat("Roughness", &materialComponent->roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ao", &materialComponent->ao, 0.0f, 1.0f);
			if (ImGui::Button("Remove Component"))
				ecs->RemoveComponent<MaterialComponent>(entity);
			ImGui::TreePop();
		}
	}
}
