#pragma once

#include <glad/glad.h>
#include "OpenGL/FrameBuffer.h"

class RenderBuffer {
private:
	unsigned int m_id = 0;
	unsigned int m_width = 0;
	unsigned int m_height = 0;
	GLenum m_format = GL_DEPTH24_STENCIL8;

public:
	RenderBuffer();
	RenderBuffer(const RenderBuffer&) = delete;
	RenderBuffer(RenderBuffer&& renderBuffer) noexcept;
	RenderBuffer& operator=(const RenderBuffer&) = delete;
	RenderBuffer& operator=(RenderBuffer&& renderBuffer) noexcept;
	~RenderBuffer();

	void Bind() const;
	void Unbind() const;
	unsigned int GetHandle() const { return this->m_id; }

	void InitStorage(int width, int height, GLenum format);
	void LinkToFrameBuffer(const FrameBuffer& framebuffer) const;
	void FreeRenderBuffer();

	unsigned int GetWidth() const { return this->m_width; }
	unsigned int GetHeight() const { return this->m_height; }
};
