#pragma once

#include "Kikurage/ECS/ECS.h"
#include "Kikurage/ECS/ECS_def.h"

#include "Kikurage/GUI/ComponentEditors.h"

namespace Kikurage {
	class ComponentEditor {
	private:
		std::array<std::unique_ptr<ComponentEditorBase>, MAX_COMPONENTS_FAMILY> m_componentGUIs;
		ComponentFamily m_componentGUIbit;

	public:
		ComponentEditor() {}
		~ComponentEditor() = default;

		void Init();
		void Render();
	};
}
