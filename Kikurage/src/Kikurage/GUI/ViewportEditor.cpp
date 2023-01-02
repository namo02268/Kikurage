#include "Kikurage/GUI/ViewportEditor.h"
#include "Kikurage/Core/Application/Application.h"

#include "imgui/imgui.h"

void ViewportEditor::Render() {
	// Scene Window
	ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::PushID("Scene");

	// window size
	m_width = static_cast<unsigned int>(ImGui::GetWindowWidth());
	m_height = static_cast<unsigned int>(ImGui::GetWindowHeight());
	ImGui::Image((void*)Application::GetInstance().GetRenderer()->GetRenderTexture().GetHandle(), ImVec2(m_width, m_height), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::PopID();
	ImGui::End();
}