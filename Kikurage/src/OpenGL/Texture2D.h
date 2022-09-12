#pragma once

#include <glad/glad.h>
#include <string>

class Texture2D {
private:
	std::string filepath;
	unsigned int  m_id = 0;
	unsigned int m_width = 0;
	unsigned int m_height = 0;
	unsigned int m_format = GL_RGB;
	unsigned int m_wrapType = GL_REPEAT;
	unsigned int m_filter = GL_LINEAR;

	void FreeTexture();

public:
	Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&& texture) noexcept;
	Texture2D& operator=(const Texture2D&) = delete;
	Texture2D& operator=(Texture2D&& texture) noexcept;
	~Texture2D();

	void Bind() const;
	void Unbind() const;
	unsigned int GetHandle() const { return this->m_id; }

	void Generate(unsigned char* data, unsigned int width, unsigned int height, unsigned int channels = 3, unsigned int format = GL_RGB);

	void SetWrapType(unsigned int wrapType);
	void SetFilterType(unsigned int filterType);
	unsigned int GetWidth() const { return this->m_width; }
	unsigned int GetHeight() const { return this->m_height; }
	unsigned int GetFormat() const { return this->m_format; }
};
