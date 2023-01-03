#pragma once

#include <iostream>

#include "Kikurage/GUI/ComponentEditor.h"
#include "Kikurage/GUI/Viewport.h"

namespace Kikurage {
	class GuiManager {
	private:
		std::unique_ptr<ComponentEditor> m_componentEditor = std::make_unique<ComponentEditor>();
		std::unique_ptr<Viewport> m_viewport = std::make_unique<Viewport>();

	public:
		GuiManager() = default;
		~GuiManager();

		void Init();
		void StartGUIFrame();
		void Render();
		void EndGUIFrame();

		unsigned int GetViewportWidth() const { return this->m_viewport->GetWidth(); }
		unsigned int GetViewportHeight() const { return this->m_viewport->GetHeight(); }
	};
}
