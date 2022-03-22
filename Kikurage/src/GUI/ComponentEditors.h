#pragma once
#include "ECS/Scene.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/CameraComponent.h"

//----------------------------------------------Base----------------------------------------------//
class ComponentEditorBase {
public:
	ComponentTypeID ID;
	Scene* m_parentScene;

public:
	virtual ~ComponentEditorBase() {}
	virtual void draw(Entity& e) {}
};

//----------------------------------------------Transform----------------------------------------------//
class TransfromEditor : public ComponentEditorBase {
public:
	TransfromEditor(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<TransformComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Transform")) {
			auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
			ImGui::DragFloat3("Position", &transfromComponent->position.x, 0.01f);
			ImGui::DragFloat3("Scale", &transfromComponent->scale.x, 0.01f);
			ImGui::DragFloat3("Rotation", &transfromComponent->rotation.x, 1.0f);
			if (ImGui::Button("Remove Component"))
				m_parentScene->removeComponent<TransformComponent>(e);
			ImGui::TreePop();
		}
	}
};

//----------------------------------------------Material----------------------------------------------//
class MaterialEditor : public ComponentEditorBase {
public:
	MaterialEditor(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<MaterialComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Material")) {
			auto materialComponent = m_parentScene->getComponent<MaterialComponent>(e);
			ImGui::ColorEdit3("Albedo", &materialComponent->albedo.x);
			ImGui::SliderFloat("Metallic", &materialComponent->metallic, 0.0f, 1.0f);
			ImGui::SliderFloat("Roughness", &materialComponent->roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ao", &materialComponent->ao, 0.0f, 1.0f);
			if (ImGui::Button("Remove Component"))
				m_parentScene->removeComponent<MaterialComponent>(e);
			ImGui::TreePop();
		}
	}
};

//----------------------------------------------RigidBody----------------------------------------------//
class RigidBodyEditor : public ComponentEditorBase {
public:
	RigidBodyEditor(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<RigidBodyComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("RigidBody")) {
			auto rigidBodyComponent = m_parentScene->getComponent<RigidBodyComponent>(e);
			ImGui::DragFloat3("Velocity", &rigidBodyComponent->velocity.x, 0.01f);
			ImGui::DragFloat3("Force", &rigidBodyComponent->force.x, 0.01f);
			ImGui::DragFloat("Mass", &rigidBodyComponent->mass, 0.1f);
			ImGui::SliderFloat("Restitution", &rigidBodyComponent->restitution, 0.0f, 1.0f);
			ImGui::SliderFloat("Dynamic Friction", &rigidBodyComponent->dynamicFriction, 0.0f, 1.0f);
			ImGui::SliderFloat("Static Friction", &rigidBodyComponent->staticFriction, 0.0f, 1.0f);
			ImGui::Checkbox("Is Gravity", &rigidBodyComponent->isGravity);
			ImGui::Checkbox("Is Kinematic", &rigidBodyComponent->isKinematic);
			if (ImGui::Button("Remove Component"))
				m_parentScene->removeComponent<RigidBodyComponent>(e);
			ImGui::TreePop();
		}
	}
};

//----------------------------------------------Camera----------------------------------------------//
class CameraEditor : public ComponentEditorBase {
public:
	CameraEditor(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<CameraComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Camera")) {
			auto cameraComponent = m_parentScene->getComponent<CameraComponent>(e);
			ImGui::DragFloat("Near", &cameraComponent->Near, 0.01f);
			ImGui::DragFloat("Far", &cameraComponent->Far, 1.0f);

			ImGui::TreePop();
		}
	}
};
