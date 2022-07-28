#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderBuffer.h"
#include "Kikurage/Events/WindowResizeEvent.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void ResizeBuffer(WindowResizeEvent* event);

	void BindFBO();
	void UnbindFBO();

	Texture2D* GetRenderTexture() { return &textureColorbuffer; }

private:
	// Render FBO & Texture
	Texture2D textureColorbuffer;
	FrameBuffer frameBuffer;
	RenderBuffer renderBuffer;

	void GenerateRenderTexture();
};