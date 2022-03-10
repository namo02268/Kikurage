#include "GUI.h"
#include "Scene.h"
#include "GUIComponent.h"
#include "ComponentGUIs.h"


void imgui_theme();

GUI::GUI(Window* window) {
	this->parentWindow = window;

	auto family = getComponentTypeID<GUIComponent>();
	m_requiredComponent[family] = true;
}

GUI::~GUI() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUI::init() {
	// init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(parentWindow->GetWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// imgui configuration
	imgui_theme();

	// add Component GUIs
	auto transformComponentGUI = std::make_unique<TransfromComponentGUI>(m_parentScene);
	m_componentGUIbit[transformComponentGUI->ID] = true;
	auto materialComponentGUI = std::make_unique<MaterialComponentGUI>(m_parentScene);
	m_componentGUIbit[materialComponentGUI->ID] = true;
	auto motionComponentGUI = std::make_unique<MotionComponentGUI>(m_parentScene);
	m_componentGUIbit[motionComponentGUI->ID] = true;

	m_componentGUIs[transformComponentGUI->ID] = std::move(transformComponentGUI);
	m_componentGUIs[materialComponentGUI->ID] = std::move(materialComponentGUI);
	m_componentGUIs[motionComponentGUI->ID] = std::move(motionComponentGUI);
}

void GUI::update(float dt) {
}

void GUI::draw() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Component GUI
	ImGui::SetNextWindowPos(ImVec2(parentWindow->GetWidth() - 300, 0.0));
	ImGui::SetNextWindowSize(ImVec2(300, parentWindow->GetHeight()));
	bool open;
	ImGui::Begin("Inspector", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	for (auto& e : m_entityArray) {
		ImGui::PushID(e.GetID());
		if (ImGui::CollapsingHeader(e.name.c_str())) {
			for (int i = 0; i < MAX_COMPONENTS_FAMILY; i++) {
				if (e.attachedComponent[i] && m_componentGUIbit[i]) {
					m_componentGUIs[i]->draw(e);
				}
			}
		}
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Component");

		if (ImGui::BeginPopup("Component"))
		{
			if (ImGui::Selectable("Transform"))
				m_parentScene->addComponent<TransformComponent>(e);
			if (ImGui::Selectable("Material"))
				m_parentScene->addComponent<MaterialComponent>(e);
			if (ImGui::Selectable("Motion"))
				m_parentScene->addComponent<MotionComponent>(e);
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_theme() {
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowRounding = 0.0f;
	style.FrameRounding = 0.0f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.0f, 0.0f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.6f, 0.6f, 0.6f, 0.7f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.8f, 0.8f, 0.8f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.8f, 0.8f, 0.8f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.75f, 0.75f, 0.75f, 0.9f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.9f, 0.9f, 0.9f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.9f, 0.9f, 0.9f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.9f, 0.9f, 0.9f, 0.21f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.9f, 0.9f, 0.9f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.9f, 0.9f, 0.9f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3f, 0.3f, 0.3f, 0.50f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.6f, 0.8f, 0.8f, 0.80f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.6f, 0.8f, 0.8f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.6f, 0.8f, 0.8f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.80f, 0.80f, 0.80f, 0.95f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.9f, 0.9f, 0.9f, 0.95f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.9f, 0.9f, 0.9f, 0.15f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9f, 0.9f, 0.9f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.0f, 0.0f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.0f, 0.0f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9f, 0.9f, 0.9f, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.6f, 0.6f, 0.8f, 0.92f);
}