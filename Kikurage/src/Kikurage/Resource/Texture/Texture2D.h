#pragma once

#include <glad/glad.h>

class Texture2D {
public:
	unsigned int id = 0;

	unsigned int width = 0;
	unsigned int height = 0;

	unsigned int Internal_Format = GL_RGB;
	unsigned int Image_Format = GL_RGB;

	unsigned int Wrap_S = GL_REPEAT;
	unsigned int Wrap_T = GL_REPEAT;
	unsigned int Filter_Min = GL_LINEAR;
	unsigned int Filter_Max = GL_LINEAR;

	Texture2D();
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D& texture) = delete;
	~Texture2D();

	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind() const;
	void Unbind() const;
	void FreeTexture();
};
