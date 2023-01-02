#pragma once

#include <glad/glad.h>
#include "OpenGL/Texture2D.h"

namespace Kikurage {
	class FrameBuffer {
	private:
		unsigned int m_id = 0;

		void FreeFrameBuffer();

	public:
		FrameBuffer();
		FrameBuffer(const FrameBuffer&) = delete;
		FrameBuffer(FrameBuffer&& frameBuffer) noexcept;
		FrameBuffer& operator=(const FrameBuffer&) = delete;
		FrameBuffer& operator=(FrameBuffer&& frameBuffer) noexcept;
		~FrameBuffer();

		void Bind() const;
		void Unbind() const;
		unsigned int GetHandle() const { return m_id; }
		void AttachTexture(const Texture2D& texture);

		// TODO : Get Texture Width & Height
	};
}
