#pragma once

#include <vector>
#include <glad/glad.h>
#include "OpenGL/Texture2D.h"

namespace Kikurage {
	class FrameBuffer {
	private:
		unsigned int m_id = 0;
		void FreeFrameBuffer();
		std::vector<unsigned int> m_attachments;

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

		// TODO : Automatic addition without specification of attachment number
		void AttachTexture(const Texture2D& texture, const unsigned int attachment = GL_COLOR_ATTACHMENT0);
		void DrawBuffers();
		// TODO : Get Texture Width & Height
	};
}
