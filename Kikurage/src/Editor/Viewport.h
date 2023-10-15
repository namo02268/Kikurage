#pragma once

#include "imgui/imgui.h"
#include "Kikurage/Core/Renderer/Renderer.h"

namespace Kikurage {
	void Viewport(Renderer* renderer) {
		// Scene Window
		ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PushID("Viewport");

		// window size
		auto width = ImGui::GetWindowWidth();
		auto height = ImGui::GetWindowHeight();
		renderer->SetWidth(static_cast<unsigned int>(width));
		renderer->SetHeight(static_cast<unsigned int>(height));
		ImGui::Image((void*)renderer->GetRenderTexture().GetHandle(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::PopID();
		ImGui::End();

		ImGui::Begin("Position", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PushID("Position");
		ImGui::Image((void*)renderer->GetPositionTexture().GetHandle(), ImVec2(width * 0.25f, height * 0.25f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::PopID();
		ImGui::End();

		ImGui::Begin("Normal", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PushID("Normal");
		ImGui::Image((void*)renderer->GetNormalTexture().GetHandle(), ImVec2(width * 0.25f, height * 0.25f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::PopID();
		ImGui::End();

		ImGui::Begin("Albedo", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PushID("Albedo");
		ImGui::Image((void*)renderer->GetAlbedoTexture().GetHandle(), ImVec2(width * 0.25f, height * 0.25f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::PopID();
		ImGui::End();

		ImGui::Begin("Specular", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::PushID("Specular");
		ImGui::Image((void*)renderer->GetSpecularTexture().GetHandle(), ImVec2(width * 0.25f, height * 0.25f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::PopID();
		ImGui::End();
	}
}
