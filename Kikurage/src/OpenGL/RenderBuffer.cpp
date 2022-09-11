#include "OpenGL/RenderBuffer.h"

RenderBuffer::RenderBuffer() {
	glGenRenderbuffers(1, &this->m_id);
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

void RenderBuffer::LinkToFrameBuffer(const FrameBuffer& framebuffer) const {
	framebuffer.Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_id);
	framebuffer.Unbind();
}

void RenderBuffer::Bind() const {
	glBindRenderbuffer(GL_RENDERBUFFER, this->m_id);
}

void RenderBuffer::Unbind() const {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::FreeRenderBuffer() {
	if (this->m_id != 0) {
		glDeleteRenderbuffers(1, &this->m_id);
		this->m_id = 0;
	}
}