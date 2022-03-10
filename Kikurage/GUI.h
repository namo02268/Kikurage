#pragma once

#include <array>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "System.h"
#include "Scene.h"
#include "Window.h"
#include "ECS_def.h"

#include "TransformComponent.h"
#include "MaterialComponent.h"
#include "MotionComponent.h"

class ComponentGUIBase {
public:
	ComponentTypeID ID;
	Scene* m_parentScene;

public:
	virtual ~ComponentGUIBase() {}
	virtual void draw(Entity& e) {}
};

class GUI : public System {
private:
	Window* parentWindow;
	std::array<std::unique_ptr<ComponentGUIBase>, MAX_COMPONENTS_FAMILY> m_componentGUIs;
	ComponentFamily m_componentGUIbit;

public:
	GUI(Window* window);
	~GUI();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

class TransfromComponentGUI : public ComponentGUIBase {
public:
	TransfromComponentGUI(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<TransformComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Transform")) {
			ImGui::DragFloat3("Position", &m_parentScene->getComponent<TransformComponent>(e).position.x, 0.01f);
			ImGui::DragFloat3("Scale", &m_parentScene->getComponent<TransformComponent>(e).scale.x, 0.01f);
			ImGui::DragFloat3("Rotation", &m_parentScene->getComponent<TransformComponent>(e).rotation.x, 1.0f);
			ImGui::TreePop();
		}
	}
};

class MaterialComponentGUI : public ComponentGUIBase {
public:
	MaterialComponentGUI(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<MaterialComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Material")) {
			ImGui::ColorEdit3("Albedo", &m_parentScene->getComponent<MaterialComponent>(e).albedo.x);
			ImGui::SliderFloat("Metallic", &m_parentScene->getComponent<MaterialComponent>(e).metallic, 0.0f, 1.0f);
			ImGui::SliderFloat("Roughness", &m_parentScene->getComponent<MaterialComponent>(e).roughness, 0.0f, 1.0f);
			ImGui::SliderFloat("ao", &m_parentScene->getComponent<MaterialComponent>(e).ao, 0.0f, 1.0f);
			ImGui::TreePop();
		}
	}
};

class MotionComponentGUI : public ComponentGUIBase {
public:
	MotionComponentGUI(Scene* scene) {
		m_parentScene = scene;
		ID = getComponentTypeID<MotionComponent>();
	}

	void draw(Entity& e) {
		if (ImGui::TreeNode("Motion")) {
			if (ImGui::TreeNode("Velocity")) {
				ImGui::DragFloat3("Position", &m_parentScene->getComponent<MotionComponent>(e).positionVelosity.x, 0.01f);
				ImGui::DragFloat3("Scale", &m_parentScene->getComponent<MotionComponent>(e).scaleVelosity.x, 0.01f);
				ImGui::DragFloat3("Rotation", &m_parentScene->getComponent<MotionComponent>(e).rotationVelosity.x, 1.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Acceleration")) {
				ImGui::DragFloat3("Position", &m_parentScene->getComponent<MotionComponent>(e).positionAcceleration.x, 0.01f);
				ImGui::DragFloat3("Scale", &m_parentScene->getComponent<MotionComponent>(e).scaleAcceleration.x, 0.01f);
				ImGui::DragFloat3("Rotation", &m_parentScene->getComponent<MotionComponent>(e).rotationAcceleration.x, 1.0f);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
};
