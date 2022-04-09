#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Kikurage/Resource/Texture/Texture2D.h"
#include "Kikurage/Events/WindowResizeEvent.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void ResizeBuffer(WindowResizeEvent* event);

	void BindFBO();
	void UnbindFBO();

	Texture2D& GetRenderTexture() { return textureColorbuffer; }

private:
	// Render FBO & Texture
	unsigned int framebuffer;
	unsigned int rbo;
	Texture2D textureColorbuffer;

	void GenerateRenderTexture();
};