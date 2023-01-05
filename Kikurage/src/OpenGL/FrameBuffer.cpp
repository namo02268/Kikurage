#include "OpenGL/FrameBuffer.h"

namespace Kikurage {
	FrameBuffer::FrameBuffer() {
		glGenFramebuffers(1, &this->m_id);
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;
	}

	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept {
		this->m_id = other.m_id;
		other.m_id = 0;

		return *this;
	}

	FrameBuffer::~FrameBuffer() {
		this->FreeFrameBuffer();
	}

	void FrameBuffer::AttachTexture(const Texture2D& texture) {
		this->Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetHandle(), 0);
	}


	void FrameBuffer::FreeFrameBuffer() {
		if (this->m_id != 0) {
			glDeleteFramebuffers(1, &this->m_id);
			this->m_id = 0;
		}
	}
}
