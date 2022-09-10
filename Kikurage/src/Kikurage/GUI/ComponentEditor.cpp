#include "Kikurage/GUI/ComponentEditor.h"
#include "Kikurage/Core/Application/Application.h"

void ComponentEditor::Init() {
	auto scene = Application::GetInstance().GetScene();

	// add Component GUIs
	auto transformComponentGUI = std::make_unique<TransfromEditor>(scene);
	m_componentGUIbit[transformComponentGUI->ID] = true;
	auto materialComponentGUI = std::make_unique<MaterialEditor>(scene);
	m_componentGUIbit[materialComponentGUI->ID] = true;
	auto rigidBodyComponentGUI = std::make_unique<RigidBodyEditor>(scene);
	m_componentGUIbit[rigidBodyComponentGUI->ID] = true;
	auto cameraComponentGUI = std::make_unique<CameraEditor>(scene);
	m_componentGUIbit[cameraComponentGUI->ID] = true;

	m_componentGUIs[transformComponentGUI->ID] = std::move(transformComponentGUI);
	m_componentGUIs[materialComponentGUI->ID] = std::move(materialComponentGUI);
	m_componentGUIs[rigidBodyComponentGUI->ID] = std::move(rigidBodyComponentGUI);
	m_componentGUIs[cameraComponentGUI->ID] = std::move(cameraComponentGUI);
}

void ComponentEditor::Render() {
	auto scene = Application::GetInstance().GetScene();

	// Hierarchy
	ImGui::Begin("Hierarchy");
	ImGui::PushID("Hierarchy");

	auto& entityArray = scene->getAllEntityArray();

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
		ImGui::PushID(entityArray[selected]);
		for (int i = 0; i < MAX_COMPONENTS_FAMILY; i++) {
			if (scene->getComponentMask(entityArray[selected])[i] && m_componentGUIbit[i]) {
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
				scene->addComponent<TransformComponent>(entityArray[selected], TransformComponent());
			if (ImGui::Selectable("Material"))
				scene->addComponent<MaterialComponent>(entityArray[selected], MaterialComponent());
			if (ImGui::Selectable("RigidBody"))
				scene->addComponent<RigidBodyComponent>(entityArray[selected], RigidBodyComponent());
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}

	ImGui::PopItemWidth();
	ImGui::End();
}
