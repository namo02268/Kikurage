#include "GUI/Editor.h"

void Editor::init() {
	// add Component GUIs
	auto transformComponentGUI = std::make_unique<TransfromEditor>(m_parentScene);
	m_componentGUIbit[transformComponentGUI->ID] = true;
	auto materialComponentGUI = std::make_unique<MaterialEditor>(m_parentScene);
	m_componentGUIbit[materialComponentGUI->ID] = true;
	auto rigidBodyComponentGUI = std::make_unique<RigidBodyEditor>(m_parentScene);
	m_componentGUIbit[rigidBodyComponentGUI->ID] = true;
	auto cameraComponentGUI = std::make_unique<CameraEditor>(m_parentScene);
	m_componentGUIbit[cameraComponentGUI->ID] = true;

	m_componentGUIs[transformComponentGUI->ID] = std::move(transformComponentGUI);
	m_componentGUIs[materialComponentGUI->ID] = std::move(materialComponentGUI);
	m_componentGUIs[rigidBodyComponentGUI->ID] = std::move(rigidBodyComponentGUI);
	m_componentGUIs[cameraComponentGUI->ID] = std::move(cameraComponentGUI);
}

void Editor::draw() {
	// Hierarchy
	ImGui::Begin("Hierarchy");
	ImGui::PushID("Hierarchy");

	auto& entityArray = m_parentScene->getAllEntityArray();

	static int selected = -1;
	char buf[32];
	for (int n = 0; n < entityArray.size(); n++) {
		sprintf_s(buf, "Entity %d", entityArray[n]);
		if (ImGui::Selectable(buf, selected == n)) {
			selected = n;
		}
	}

	ImGui::PopID();
	ImGui::End();

	// Component Editor
	ImGui::Begin("Inspector");
	ImGui::PushItemWidth(200);

	if (selected != -1) {
		ImGui::PushID(entityArray[selected].GetID());
		for (int i = 0; i < MAX_COMPONENTS_FAMILY; i++) {
			if (m_parentScene->getComponentMask(entityArray[selected])[i] && m_componentGUIbit[i]) {
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);
				m_componentGUIs[i]->draw(entityArray[selected]);
				ImGui::Separator();
			}
		}

		ImGui::PushItemWidth(50.0f);
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Component");

		if (ImGui::BeginPopup("Component"))
		{
			if (ImGui::Selectable("Transform"))
				m_parentScene->addComponent<TransformComponent>(entityArray[selected]);
			if (ImGui::Selectable("Material"))
				m_parentScene->addComponent<MaterialComponent>(entityArray[selected]);
			if (ImGui::Selectable("RigidBody"))
				m_parentScene->addComponent<RigidBodyComponent>(entityArray[selected]);
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}

	ImGui::PopItemWidth();
	ImGui::End();
}
