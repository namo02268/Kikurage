#pragma once

#include "ECS/Scene.h"
#include "ECS/ECS_def.h"

#include "GUI/ComponentEditors.h"

class Editor {
private:
	Scene* m_parentScene;
	std::array<std::unique_ptr<ComponentEditorBase>, MAX_COMPONENTS_FAMILY> m_componentGUIs;
	ComponentFamily m_componentGUIbit;

public:
	Editor(Scene* scene) : m_parentScene(scene) { init(); }
	~Editor() = default;

	void init();
	void draw();
};