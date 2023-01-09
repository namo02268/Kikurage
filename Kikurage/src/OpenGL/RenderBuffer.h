#pragma once

#include <glad/glad.h>
#include "OpenGL/FrameBuffer.h"

namespace Kikurage {
	class RenderBuffer {
	private:
		unsigned int m_id = 0;
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		GLenum m_format = GL_DEPTH_COMPONENT;

		void FreeRenderBuffer();

	public:
		RenderBuffer();
		RenderBuffer(const RenderBuffer&) = delete;
		RenderBuffer(RenderBuffer&& other) noexcept;
		RenderBuffer& operator=(const RenderBuffer&) = delete;
		RenderBuffer& operator=(RenderBuffer&& other) noexcept;
		~RenderBuffer();

		void Bind() const { glBindRenderbuffer(GL_RENDERBUFFER, this->m_id); }
		void Unbind() const { glBindRenderbuffer(GL_RENDERBUFFER, 0); }
		const unsigned int GetHandle() const { return this->m_id; }

		void InitStorage(int width, int height, GLenum format);
		void LinkToFrameBuffer(const FrameBuffer& framebuffer, unsigned int mode) const; // TODO : bool isBind()?

		unsigned int GetWidth() const { return this->m_width; }
		unsigned int GetHeight() const { return this->m_height; }
	};
}
