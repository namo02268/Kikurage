#pragma once

#include <glad/glad.h>
#include "OpenGL/Texture2D.h"

class FrameBuffer {
public:
	unsigned int id = 0;

public:
	FrameBuffer();
	FrameBuffer(const FrameBuffer&) = delete;
	FrameBuffer& operator=(const FrameBuffer&) = delete;
	~FrameBuffer();

	void AttachTexture(const Texture2D& texture);
	void Bind() const;
	void Unbind() const;
	void FreeFrameBuffer();

	// TODO : Get Texture Width & Height
};