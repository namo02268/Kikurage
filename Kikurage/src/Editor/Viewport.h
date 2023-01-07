#pragma once

#include "imgui/imgui.h"
#include "Kikurage/Core/Renderer/Renderer.h"

namespace Kikurage {
	void Viewport(Renderer* renderer) {
		// Scene Window
		ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PushID("Scene");

		// window size
		auto width = ImGui::GetWindowWidth();
		auto height = ImGui::GetWindowHeight();
		renderer->SetWidth(static_cast<unsigned int>(width));
		renderer->SetHeight(static_cast<unsigned int>(height));
		ImGui::Image((void*)renderer->GetRenderTexture().GetHandle(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::PopID();
		ImGui::End();
	}
}
