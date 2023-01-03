#pragma once

namespace Kikurage {
	class Viewport {
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;

	public:
		Viewport() = default;
		~Viewport() = default;

		void Render();

		unsigned int GetWidth() { return this->m_width; }
		unsigned int GetHeight() { return this->m_height; }
	};
}
