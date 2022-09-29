#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Core/Event.h"

//---------------------RenderBuffers---------------------//
void RenderBuffers::Init(int width, int height) {
	this->renderTexture.Generate(nullptr, width, height);
	this->framebuffer.AttachTexture(this->renderTexture);
	this->renderbuffer.InitStorage(width, height, GL_DEPTH24_STENCIL8);
	this->renderbuffer.LinkToFrameBuffer(this->framebuffer, GL_DEPTH_STENCIL_ATTACHMENT);
}

void RenderBuffers::Resize(int width, int height) {
	this->renderTexture.Generate(nullptr, width, height);
	this->renderbuffer.InitStorage(width, height, GL_DEPTH24_STENCIL8);
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

void Renderer::Start() {
	this->BindFBO();
}

void Renderer::End() {
	this->UnbindFBO();
}

void Renderer::ResizeBuffers(int width, int height) {
	this->renderBuffers->Resize(width, height);
}

void Renderer::ListenWindowResizeEvent(WindowResizeEvent* event) {
	this->m_renderSettings.width = event->width;
	this->m_renderSettings.height = event->height;
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

void Renderer::BindCameraInformation(BaseCamera* camera, const TransformComponent* transform) {
	for (auto shader : m_shaders) {
		auto view = glm::inverse(transform->worldMatrix);

		camera->SetAspectRatio(static_cast<float>(this->GetWidth()) / static_cast<float>(this->GetHeight()));

		shader->Bind();
		shader->SetUniform("cameraPos", transform->position);
		shader->SetUniform("projection", camera->GetProjectionMatrix());
		shader->SetUniform("view", view);
	}
}
