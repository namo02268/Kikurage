#pragma once

#include <glad/glad.h>

class Texture2D {
// TODO : make variables private
private:
	using TextureID = unsigned int;
	TextureID m_id = 0;

	unsigned int m_width = 0;
	unsigned int m_height = 0;
	unsigned int m_format = GL_RGB;

public:
	unsigned int Wrap_S = GL_REPEAT;
	unsigned int Wrap_T = GL_REPEAT;
	unsigned int Filter_Min = GL_LINEAR;
	unsigned int Filter_Max = GL_LINEAR;

public:
	Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&& texture) noexcept;
	Texture2D& operator=(const Texture2D& texture) = delete;
	Texture2D& operator=(Texture2D&& texture) noexcept;
	~Texture2D();

	TextureID GetHandle() const { return m_id; }
	void Generate(unsigned int width, unsigned int height, unsigned int channels, unsigned int format, unsigned char* data);
	void Bind() const;
	void Unbind() const;
	void FreeTexture();
};
