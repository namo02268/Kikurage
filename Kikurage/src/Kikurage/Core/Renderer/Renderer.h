#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderBuffer.h"
#include "Kikurage/Events/WindowResizeEvent.h"

struct RenderBuffers {
	Texture2D renderTexture;
	FrameBuffer framebuffer;
	RenderBuffer renderbuffer;

	void Init(int width, int height);
	void Resize(int width, int height);
};


class Renderer {
private:
	std::unique_ptr<RenderBuffers> renderBuffers = std::make_unique<RenderBuffers>();

public:
	Renderer();
	virtual ~Renderer();

	void Init();

	void ResizeBuffers(int width, int height);
	void ListenWindowResizeEvent(WindowResizeEvent* event);

	void BindFBO();
	void UnbindFBO();

	Texture2D& GetRenderTexture() { return this->renderBuffers->renderTexture; }

	struct RenderSettings {

	};

};