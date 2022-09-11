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
	unsigned int m_wrapType = GL_REPEAT;
	unsigned int m_filter = GL_LINEAR;

public:
	Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&& texture) noexcept;
	Texture2D& operator=(const Texture2D& texture) = delete;
	Texture2D& operator=(Texture2D&& texture) noexcept;
	~Texture2D();

	TextureID GetHandle() const { return m_id; }
	void Bind() const;
	void Unbind() const;

	void Generate(unsigned char* data, unsigned int width, unsigned int height, unsigned int channels = 3, unsigned int format = GL_RGB);
	void FreeTexture();

	void SetWrapType(unsigned int wrapType);
	void SetFilterType(unsigned int filterType);
};
