#include "OpenGL/RenderBuffer.h"

RenderBuffer::RenderBuffer() {
	glGenRenderbuffers(1, &this->m_id);
}

RenderBuffer::RenderBuffer(RenderBuffer&& renderBuffer) noexcept {
	this->m_id = renderBuffer.m_id;
	renderBuffer.m_id = 0;
}

RenderBuffer& RenderBuffer::operator=(RenderBuffer&& renderBuffer) noexcept {
	this->m_id = renderBuffer.m_id;
	renderBuffer.m_id = 0;

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