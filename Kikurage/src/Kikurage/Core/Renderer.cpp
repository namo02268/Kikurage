#include "Kikurage/Core/Renderer.h"
#include "Kikurage/Core/Event.h"

#include <iostream>

Renderer::Renderer() {
	Event::subscribe(this, &Renderer::ResizeBuffer);
	GenerateRenderTexture();
}

Renderer::~Renderer() {
}

void Renderer::GenerateRenderTexture() {
	textureColorbuffer.Generate(1920, 1080, NULL);
	frameBuffer.AttachTexture(textureColorbuffer);
	renderBuffer.InitStorage(1920, 1080);
	renderBuffer.LinkToFrameBuffer(frameBuffer);
}

void Renderer::ResizeBuffer(WindowResizeEvent* event) {
	textureColorbuffer.Generate(event->width, event->height, NULL);
	frameBuffer.AttachTexture(textureColorbuffer);
	renderBuffer.InitStorage(event->width, event->height);
	renderBuffer.LinkToFrameBuffer(frameBuffer);
}

void Renderer::BindFBO() {
	frameBuffer.Bind();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::UnbindFBO() { 
	frameBuffer.Unbind();
}
