#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	//---------------------RenderBuffers---------------------//
	void RenderBuffers::Init() {
		this->renderTexture.Generate(nullptr, 0, 0);
		this->framebuffer.AttachTexture(this->renderTexture);
		this->renderbuffer.InitStorage(0, 0, GL_DEPTH24_STENCIL8);
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
		this->renderBuffers->Init();
	}

	void Renderer::Start() {
		this->ResizeViewport();
		this->BindFBO();
	}

	void Renderer::End() {
		this->UnbindFBO();
	}

	void Renderer::ResizeViewport() {
		auto& app = Application::GetInstance();
		unsigned int width = 0;
		unsigned int height = 0;
		if (app.isEditorEnable) {
			width = app.GetGUIManager()->GetViewportWidth();
			height = app.GetGUIManager()->GetViewportHeight();
		}
		else {
			width = app.GetWindow()->GetWidth();
			height = app.GetWindow()->GetHeight();
		}

		if (width != this->m_renderInfo.width || height != this->m_renderInfo.height) {
			m_renderInfo.width = width;
			m_renderInfo.height = height;
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

	void Renderer::BindCameraInformation(BaseCamera& camera, Transform& transform) {
		for (auto shader : m_shaders) {
			auto view = Inverse(transform.GetLocalMatrix());
			camera.SetAspectRatio(static_cast<float>(this->GetWidth()) / static_cast<float>(this->GetHeight()));

			shader->Bind();
			shader->SetUniform("cameraPos", transform.GetPosition());
			shader->SetUniform("projection", camera.GetProjectionMatrix());
			shader->SetUniform("view", view);
		}
	}

	void Renderer::DrawObject(Mesh* mesh) {
		mesh->Bind();
		glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, 0);
		mesh->Unbind();
	}
}
