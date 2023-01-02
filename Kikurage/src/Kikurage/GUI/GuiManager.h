#pragma once

#include <iostream>

#include "Kikurage/GUI/ComponentEditor.h"
#include "Kikurage/GUI/ViewportEditor.h"

namespace Kikurage {
	class GuiManager {
	private:
		std::unique_ptr<ComponentEditor> m_componentEditor = std::make_unique<ComponentEditor>();
		std::unique_ptr<ViewportEditor> m_sceneEditor = std::make_unique<ViewportEditor>();

	public:
		GuiManager() = default;
		~GuiManager();

		void Init();
		void StartGUIFrame();
		void Render();
		void EndGUIFrame();

		unsigned int GetViewportWidth() const { return this->m_sceneEditor->GetWidth(); }
		unsigned int GetViewportHeight() const { return this->m_sceneEditor->GetHeight(); }

	private:
		void BeginDockSpace();
	};
}
