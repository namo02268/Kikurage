#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Kikurage/Resource/Texture/Texture2D.h"

class Renderer {
public:
	Renderer() { GenerateRenderTexture(); }
	virtual ~Renderer() { glDeleteFramebuffers(1, &framebuffer); }

	void BindFBO();
	void UnbindFBO();

	Texture2D& GetRenderTexture() { return textureColorbuffer; }

private:
	// Render FBO & Texture
	unsigned int framebuffer;
	Texture2D textureColorbuffer;

	void GenerateRenderTexture();
};