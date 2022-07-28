#include "Kikurage/Resource/FrameBuffer/FrameBuffer.h"

FrameBuffer::FrameBuffer() {
	glGenFramebuffers(1, &this->id);
}

FrameBuffer::~FrameBuffer() {
	this->FreeFrameBuffer();
}

void FrameBuffer::AttachTexture(const Texture2D& texture) {
	this->Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
}

void FrameBuffer::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, this->id);
}

void FrameBuffer::Unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::FreeFrameBuffer() {
	if (this->id != 0) {
		glDeleteFramebuffers(1, &id);
		this->id = 0;
	}
}