#include "OpenGL/RenderBuffer.h"

RenderBuffer::RenderBuffer() {
	glGenRenderbuffers(1, &this->id);
}

RenderBuffer::~RenderBuffer() {
	this->FreeRenderBuffer();
}

void RenderBuffer::InitStorage(int width, int height) {
	this->width = width;
	this->height = height;

	this->Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void RenderBuffer::LinkToFrameBuffer(const FrameBuffer& framebuffer) const {
	framebuffer.Bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->id);
	framebuffer.Unbind();
}

void RenderBuffer::Bind() const {
	glBindRenderbuffer(GL_RENDERBUFFER, this->id);
}

void RenderBuffer::Unbind() const {
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::FreeRenderBuffer() {
	if (this->id != 0) {
		glDeleteRenderbuffers(1, &this->id);
		this->id = 0;
	}
}