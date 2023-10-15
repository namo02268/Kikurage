#pragma once
#include "Kikurage/Core/ECS/ECS.h"
#include "imgui/imgui.h"

#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Material/Material.h"
#include "Kikurage/Components/Light/Light.h"

namespace Kikurage {
	void TransformEditor(Nameko::Entity entity, KikurageECS* ecs) {
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

	void CameraEditor(Nameko::Entity entity, KikurageECS* ecs) {
		if (ImGui::TreeNode("Camera")) {
			auto camera = ecs->GetComponent<Camera>(entity);
			auto fov = camera->GetFOV();
			auto near = camera->GetNear();
			auto far = camera->GetFar();
			auto speed = camera->GetCameraSpeed();
			auto sensitivity = camera->GetMouseSensitivity();

			ImGui::Text("Aspect Ratio: %f", camera->GetAspectRatio());
			if (ImGui::DragFloat("FOV", &fov, 0.01f)) { camera->SetFOV(fov); }
			if (ImGui::DragFloat("Near", &near, 0.01f)) { camera->SetNear(near); }
			if (ImGui::DragFloat("Far", &far, 10.0f)) { camera->SetFar(far); }
			if (ImGui::DragFloat("Camera Speed", &speed, 1.0f)) { camera->SetCameraSpeed(speed); }
			if (ImGui::DragFloat("Mouse Sensitivity", &sensitivity, 0.00001f)) { camera->SetMouseSensitivity(sensitivity); }

			if (ImGui::Button("Remove Component"))
				ecs->RemoveComponent<Camera>(entity);
			ImGui::TreePop();
		}
	}

	void LightEditor(Nameko::Entity entity, KikurageECS* ecs) {
		if (ImGui::TreeNode("Light")) {
			ImGui::ColorEdit3("Light Color", (float*)&ecs->GetComponent<Light>(entity)->color);
		}
	}

	void MaterialEditor(Nameko::Entity entity, KikurageECS* ecs) {
		if (ImGui::TreeNode("Material")) {
			auto material = ecs->GetComponent<Material>(entity);
			ImGui::ColorEdit3("Albedo", &material->albedo.x);
			ImGui::SliderFloat("Metallic", &material->metallic, 0.0f, 1.0f);
			ImGui::SliderFloat("Roughness", &material->roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ao", &material->ao, 0.0f, 1.0f);
			if (ImGui::Button("Remove Component"))
				ecs->RemoveComponent<Material>(entity);
			ImGui::TreePop();
		}
	}
}
