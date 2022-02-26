#pragma once

#include <glad/glad.h>

class Texture2D {
public:
	// holds the ID of the texture object
	unsigned int ID;

	// texture image dimensions
	unsigned int Width, Height;

	//texture Format
	unsigned int Internal_Format;	// format of texture object
	unsigned int Image_Format;		// format of loaded image

	// texture configuration
	unsigned int Wrap_S; // wrapping mode on S axis
	unsigned int Wrap_T; // wrapping mode on T axis
	unsigned int Filter_Min;
	unsigned int Filter_Max;

	// constructor
	Texture2D();

	// generatees texture form image data
	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	// binds the texture from image data
	void Bind() const;
};
