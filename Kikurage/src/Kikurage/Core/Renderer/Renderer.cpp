#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Core/Event.h"

#include <iostream>

//---------------------RenderBuffers---------------------//
void RenderBuffers::Init(int width, int height) {
	this->renderTexture.Generate(width, height, NULL);
	this->framebuffer.AttachTexture(this->renderTexture);
	this->renderbuffer.InitStorage(width, height);
	this->renderbuffer.LinkToFrameBuffer(this->framebuffer);
}

void RenderBuffers::Resize(int width, int height) {
	this->renderTexture.Generate(width, height, NULL);
	this->renderbuffer.InitStorage(width, height);
}

//---------------------Renderer---------------------//
Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::Init() {
	Event::subscribe(this, &Renderer::ListenWindowResizeEvent);
	this->renderBuffers->Init(1920, 1080);
}

void Renderer::ResizeBuffers(int width, int height) {
	this->renderBuffers->Resize(width, height);
}

void Renderer::ListenWindowResizeEvent(WindowResizeEvent* event) {
	this->ResizeBuffers(event->width, event->height);
}

void Renderer::BindFBO() {
	this->renderBuffers->framebuffer.Bind();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::UnbindFBO() { 
	this->renderBuffers->framebuffer.Unbind();
}
