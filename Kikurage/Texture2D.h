#pragma once

#include <glad/glad.h>

class Texture2D {
public:
	// texture ID
	unsigned int ID;

	// texture dimention
	unsigned int Width, Height;

	//texture Format
	unsigned int Internal_Format;
	unsigned int Image_Format;

	// texture configuration
	unsigned int Wrap_S;
	unsigned int Wrap_T;
	unsigned int Filter_Min;
	unsigned int Filter_Max;

	// constructor
	Texture2D();

	// generatees texture form image data
	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	// binds the texture from image data
	void Bind() const;
};
