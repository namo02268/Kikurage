#include "OpenGL/RenderBuffer.h"

namespace Kikurage {
	RenderBuffer::RenderBuffer() {
		glGenRenderbuffers(1, &this->m_id);
	}

	RenderBuffer::RenderBuffer(RenderBuffer&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;
	}

	RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;

		return *this;
	}

	RenderBuffer::~RenderBuffer() {
		this->FreeRenderBuffer();
	}

	void RenderBuffer::InitStorage(int width, int height, GLenum format) {
		this->m_width = width;
		this->m_height = height;
		this->m_format = format;

		this->Bind();
		glRenderbufferStorage(GL_RENDERBUFFER, m_format, m_width, m_height);
	}

	void RenderBuffer::LinkToFrameBuffer(const FrameBuffer& framebuffer, unsigned int mode) const {
		framebuffer.Bind();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, mode, GL_RENDERBUFFER, this->m_id);
		framebuffer.Unbind();
	}

	void RenderBuffer::FreeRenderBuffer() {
		if (this->m_id != 0) {
			glDeleteRenderbuffers(1, &this->m_id);
			this->m_id = 0;
		}
	}
}
