#include "Kikurage/GUI/ComponentEditor.h"
#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	void ComponentEditor::Init() {
		auto scene = Application::GetInstance().GetECS();

		// add Component GUIs
		auto transformComponentGUI = std::make_unique<TransfromEditor>(scene);
		m_componentGUIbit[transformComponentGUI->ID] = true;
		auto materialComponentGUI = std::make_unique<MaterialEditor>(scene);
		m_componentGUIbit[materialComponentGUI->ID] = true;
		auto rigidBodyComponentGUI = std::make_unique<RigidBodyEditor>(scene);
		m_componentGUIbit[rigidBodyComponentGUI->ID] = true;

		m_componentGUIs[transformComponentGUI->ID] = std::move(transformComponentGUI);
		m_componentGUIs[materialComponentGUI->ID] = std::move(materialComponentGUI);
		m_componentGUIs[rigidBodyComponentGUI->ID] = std::move(rigidBodyComponentGUI);
	}

	void ComponentEditor::Render() {
		auto ecs = Application::GetInstance().GetECS();

		// Hierarchy
		ImGui::Begin("Hierarchy");
		ImGui::PushID("Hierarchy");

		auto& entityArray = ecs->GetAllEntityArray();

		static EntityID selected = 0;
		ImGui::Indent();
		for (int n = 0; n < entityArray.size(); n++) {
			auto currentEntity = entityArray[n];
			if (!ecs->GetComponent<Relationship>(currentEntity)->parent) {
				auto& name = ecs->GetComponent<Name>(currentEntity)->GetName();
				auto next = ecs->GetComponent<Relationship>(currentEntity)->first;
				if (next) {
					ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
					ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
					if(selected == currentEntity) node_flags |= ImGuiTreeNodeFlags_Selected;
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)currentEntity, node_flags, name.c_str());
					if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
						selected = currentEntity;
					if (node_open) {
						if (ImGui::IsItemClicked()) {
							selected = currentEntity;
						}
						ImGui::Indent();
						while (next) {
							auto& childname = ecs->GetComponent<Name>(next)->GetName();
							if (ImGui::Selectable(childname.c_str(), selected == next)) {
								selected = next;
							}
							next = ecs->GetComponent<Relationship>(next)->next;
						}
						ImGui::TreePop();
					}
				}
				else {
					if (ImGui::Selectable(name.c_str(), selected == currentEntity)) {
						selected = currentEntity;
					}
				}
			}
		}

		// Component Editor
		ImGui::Begin("Inspector");
		ImGui::PushItemWidth(200);

		if (selected != 0) {
			ImGui::PushID(selected);
			for (int i = 0; i < MAX_COMPONENTS_FAMILY; i++) {
				if (ecs->GetComponentMask(selected)[i] && m_componentGUIbit[i]) {
					ImGui::SetNextItemOpen(true, ImGuiCond_Once);
					m_componentGUIs[i]->draw(selected);
					ImGui::Separator();
				}
			}

			ImGui::PushItemWidth(50.0f);
			if (ImGui::Button("Add Component")) {
				ImGui::OpenPopup("Component");
			}

			if (ImGui::BeginPopup("Component"))
			{
				if (ImGui::Selectable("Transform"))
					ecs->AddComponent<Transform>(selected, Transform());
				if (ImGui::Selectable("Material"))
					ecs->AddComponent<MaterialComponent>(selected, MaterialComponent());
				if (ImGui::Selectable("RigidBody"))
					ecs->AddComponent<RigidBodyComponent>(selected, RigidBodyComponent());
				ImGui::EndPopup();
			}
			ImGui::PopID();
		}

		ImGui::PopItemWidth();
		ImGui::End();

		ImGui::PopID();
		ImGui::End();
	}
}
