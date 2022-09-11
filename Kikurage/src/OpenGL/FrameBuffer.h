#pragma once

#include <glad/glad.h>
#include "OpenGL/Texture2D.h"

class FrameBuffer {
private:
	unsigned int m_id = 0;

public:
	FrameBuffer();
	FrameBuffer(const FrameBuffer&) = delete;
	FrameBuffer& operator=(const FrameBuffer&) = delete;
	~FrameBuffer();

	unsigned int GetHandle() const { return m_id; }

	void AttachTexture(const Texture2D& texture);
	void Bind() const;
	void Unbind() const;
	void FreeFrameBuffer();

	// TODO : Get Texture Width & Height
};