#pragma once

#include <glad/glad.h>
#include "OpenGL/FrameBuffer.h"

class RenderBuffer {
public:
	unsigned int id = 0;
	unsigned int width = 0;
	unsigned int height = 0;

public:
	RenderBuffer();
	RenderBuffer(const RenderBuffer&) = delete;
	RenderBuffer& operator=(const RenderBuffer&) = delete;
	~RenderBuffer();

	unsigned int GetWidth() const { return this->width; }
	unsigned int GetHeight() const { return this->height; }
	void InitStorage(int width, int height);
	void LinkToFrameBuffer(const FrameBuffer& framebuffer) const;
	void Bind() const;
	void Unbind() const;
	void FreeRenderBuffer();
};
