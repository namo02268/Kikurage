#pragma once

#include "Kikurage/ECS/Scene.h"
#include "Kikurage/ECS/ECS_def.h"

#include "Kikurage/GUI/ComponentEditors.h"

class SceneEditor {
private:
	Scene* m_parentScene;
	std::array<std::unique_ptr<ComponentEditorBase>, MAX_COMPONENTS_FAMILY> m_componentGUIs;
	ComponentFamily m_componentGUIbit;

public:
	SceneEditor(Scene* scene) : m_parentScene(scene) { init(); }
	~SceneEditor() = default;

	void init();
	void draw();
};