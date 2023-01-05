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
		FrameBuffer(FrameBuffer&& other) noexcept;
		FrameBuffer& operator=(const FrameBuffer&) = delete;
		FrameBuffer& operator=(FrameBuffer&& other) noexcept;
		~FrameBuffer();

		void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, this->m_id); }
		void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
		const unsigned int GetHandle() const { return m_id; }

		void AttachTexture(const Texture2D& texture);

		// TODO : Get Texture Width & Height
	};
}
