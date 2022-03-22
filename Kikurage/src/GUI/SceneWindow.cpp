#include "GUI/SceneWindow.h"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


SceneWindow::SceneWindow(int width, int height, const char* title) {
	m_width = width;
	m_height = height;
	m_title = title;
}

void SceneWindow::draw(unsigned int renderTexture) {
	// Scene Window
	ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoScrollbar);
	ImGui::PushID("Scene");

	// mouse
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (ImGui::IsWindowHovered()) {
		for (size_t i = 0; i < 5; i++) {
			m_mouseHeld[i] = ImGui::IsMouseDown(i);
			m_mousePressed[i] = ImGui::IsMouseClicked(i);
			m_mouseReleased[i] = ImGui::IsMouseReleased(i);
		}
		m_cursorPos[0] = io.MousePos.x;
		m_cursorPos[1] = io.MousePos.y;
	}

	// key
	for (ImGuiKey key = 0; key < 350; key++) {
		m_keyHeld[key] = ImGui::IsKeyDown(key);
		m_keyPressed[key] = ImGui::IsKeyPressed(key);
		m_keyReleased[key] = ImGui::IsKeyReleased(key);
	}

	// window size
	m_width = ImGui::GetWindowWidth();
	m_height = ImGui::GetWindowHeight();
	ImGui::Image((void*)renderTexture, ImVec2(m_width, m_height), ImVec2(0, (float)m_height / 1080), ImVec2((float)m_width / 1920, 0));

	ImGui::PopID();
	ImGui::End();
}
