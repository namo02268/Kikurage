#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Core/Application/Application.h"

namespace Kikurage {
	//---------------------RenderBuffers---------------------//
	void RenderBuffers::Init() {
		this->renderTexture.Generate(nullptr, 0, 0);
		this->framebuffer.AttachTexture(this->renderTexture);
		this->renderbuffer.InitStorage(0, 0, GL_DEPTH_COMPONENT);
		this->renderbuffer.LinkToFrameBuffer(this->framebuffer, GL_DEPTH_ATTACHMENT);
	}

	void RenderBuffers::Resize(unsigned int width, unsigned int height) {
		this->renderTexture.Generate(nullptr, width, height);
		this->renderbuffer.InitStorage(width, height, GL_DEPTH_COMPONENT);
	}

	void GBuffers::Init() {
		// position
		this->Position.Generate(nullptr, 0, 0, 4, GL_RGBA16F, GL_FLOAT);
		this->Position.SetFilterType(GL_NEAREST);
		this->gBuffer.AttachTexture(this->Position, GL_COLOR_ATTACHMENT0);
		// normal
		this->Normal.Generate(nullptr, 0, 0, 4, GL_RGBA16F, GL_FLOAT);
		this->Normal.SetFilterType(GL_NEAREST);
		this->gBuffer.AttachTexture(this->Normal, GL_COLOR_ATTACHMENT1);
		// albedo
		this->Albedo.Generate(nullptr, 0, 0, 4, GL_RGBA, GL_UNSIGNED_BYTE);
		this->Albedo.SetFilterType(GL_NEAREST);
		this->gBuffer.AttachTexture(this->Albedo, GL_COLOR_ATTACHMENT2);
		// specular
		this->Specular.Generate(nullptr, 0, 0, 4, GL_RGBA, GL_UNSIGNED_BYTE);
		this->Specular.SetFilterType(GL_NEAREST);
		this->gBuffer.AttachTexture(this->Specular, GL_COLOR_ATTACHMENT3);

		this->gBuffer.DrawBuffers();
		this->renderbuffer.InitStorage(0, 0, GL_DEPTH_COMPONENT);
		this->renderbuffer.LinkToFrameBuffer(this->gBuffer, GL_DEPTH_ATTACHMENT);
	}

	void GBuffers::Resize(unsigned int width, unsigned int height) {
		// position
		this->Position.Generate(nullptr, width, height, 4, GL_RGBA16F, GL_FLOAT);
		this->Normal.Generate(nullptr, width, height, 4, GL_RGBA16F, GL_FLOAT);
		this->Albedo.Generate(nullptr, width, height, 4, GL_RGBA, GL_UNSIGNED_BYTE);
		this->Specular.Generate(nullptr, width, height, 4, GL_RGBA, GL_UNSIGNED_BYTE);
		this->gBuffer.DrawBuffers();
		this->renderbuffer.InitStorage(width, height, GL_DEPTH_COMPONENT);
	}

	//---------------------Renderer---------------------//
	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::Init() {
		this->gBuffers->Init();
	}

	void Renderer::Start() {
		this->ResizeViewport();
		if (!IsDefaultFboEnable) {
			this->BindFBO();
		}
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::End() {
		this->UnbindFBO();
	}

	void Renderer::ResizeViewport() {
		auto& app = Application::GetInstance();
		if (IsDefaultFboEnable) {
			m_renderInfo.width = app.GetWindow()->GetWidth();
			m_renderInfo.height = app.GetWindow()->GetHeight();
		}

		if (m_renderInfo.lastWidth != this->m_renderInfo.width || m_renderInfo.lastHeight != this->m_renderInfo.height) {
			m_renderInfo.lastWidth = m_renderInfo.width;
			m_renderInfo.lastHeight = m_renderInfo.lastHeight;
			this->gBuffers->Resize(m_renderInfo.width, m_renderInfo.height);
			glViewport(0, 0, m_renderInfo.width, m_renderInfo.height);
		}
	}

	void Renderer::BindFBO() {
		this->gBuffers->gBuffer.Bind();
	}

	void Renderer::UnbindFBO() {
		this->gBuffers->gBuffer.Unbind();
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
