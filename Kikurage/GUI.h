#pragma once

#include <array>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "System.h"
#include "Window.h"
#include "ECS_def.h"

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

