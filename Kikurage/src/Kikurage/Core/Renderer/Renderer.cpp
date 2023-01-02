#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	//---------------------RenderBuffers---------------------//
	void RenderBuffers::Init(unsigned int width, unsigned int height) {
		this->renderTexture.Generate(nullptr, width, height);
		this->framebuffer.AttachTexture(this->renderTexture);
		this->renderbuffer.InitStorage(width, height, GL_DEPTH24_STENCIL8);
		this->renderbuffer.LinkToFrameBuffer(this->framebuffer, GL_DEPTH_STENCIL_ATTACHMENT);
	}

	void RenderBuffers::Resize(unsigned int width, unsigned int height) {
		this->renderTexture.Generate(nullptr, width, height);
		this->renderbuffer.InitStorage(width, height, GL_DEPTH24_STENCIL8);
	}

	//---------------------Renderer---------------------//
	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::Init() {
		unsigned int width = 1200;
		unsigned int height = 800;
		this->renderBuffers->Init(width, height);
		this->m_renderSettings.width = width;
		this->m_renderSettings.height = height;
	}

	void Renderer::Start() {
		this->BindFBO();
		this->ResizeViewport();
	}

	void Renderer::End() {
		this->UnbindFBO();
	}

	void Renderer::ResizeViewport() {
		auto width = Application::GetInstance().GetGUIManager()->GetViewportWidth();
		auto height = Application::GetInstance().GetGUIManager()->GetViewportHeight();

		if (width != this->m_renderSettings.width || height != this->m_renderSettings.height) {
			m_renderSettings.width = width;
			m_renderSettings.height = height;
			this->renderBuffers->Resize(width, height);
			glViewport(0, 0, width, height);
		}
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
}
