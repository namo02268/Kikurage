#include "Kikurage/Core/Renderer/Renderer.h"
#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

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
		this->gBufferShader = ResourceManager::LoadShader("resources/shaders/gBuffer.vert", "resources/shaders/gBuffer.frag", nullptr, "GBuffer");
		this->lightingShader = ResourceManager::LoadShader("resources/shaders/deferred_shading.vert", "resources/shaders/deferred_shading.frag", nullptr, "DeferredShading");
		this->lightCubeShader = ResourceManager::LoadShader("resources/shaders/light_cube.vert", "resources/shaders/light_cube.frag", nullptr, "LightCube");

		this->lightingShader->SetUniform("gPosition", 0);
		this->lightingShader->SetUniform("gNormal", 1);
		this->lightingShader->SetUniform("gAlbedo", 2);
		this->lightingShader->SetUniform("gSpecular", 3);

		this->gBuffers->Init();
		this->renderBuffers->Init();

		this->CreateRenderQuad();
		this->CreateLightCube();
	}

	void Renderer::StartPipeLine() {
		this->ResizeViewport();
	}

	void Renderer::GeometryPass() {
		this->gBuffers->gBuffer.Bind();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::LightingPass() {
		{
			this->renderBuffers->framebuffer.Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->lightingShader->Bind();
			this->gBuffers->Position.Bind(0);
			this->gBuffers->Normal.Bind(1);
			this->gBuffers->Albedo.Bind(2);
			this->gBuffers->Specular.Bind(3);
			this->m_renderQuad->Bind();
			glDrawElements(GL_TRIANGLES, m_renderQuad->GetIndiceCount(), GL_UNSIGNED_INT, 0);
			this->m_renderQuad->Unbind();
		}

		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, this->gBuffers->gBuffer.GetHandle());
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->renderBuffers->framebuffer.GetHandle());
			glBlitFramebuffer(0, 0, this->m_renderInfo.width, this->m_renderInfo.height, 0, 0, this->m_renderInfo.width, this->m_renderInfo.height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
			this->renderBuffers->framebuffer.Bind();
			this->lightCubeShader->Bind();

			auto ecs = Application::GetInstance().GetECS();
			ecs->EachComponent<Transform, Light>([&](Transform& transform, Light& light) {
				lightCubeShader->SetUniform("model", transform.GetWorldMatrix());
				lightCubeShader->SetUniform("lightColor", light.color);
				m_lightCube->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				m_lightCube->Unbind();
			});
		}

	}

	void Renderer::EndPipeLine() {
		/*
		if (!IsDefaultFboEnable) {
			Application::GetInstance().GetWindow()->Draw();
		}
		*/
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
			this->renderBuffers->Resize(m_renderInfo.width, m_renderInfo.height);
			glViewport(0, 0, m_renderInfo.width, m_renderInfo.height);
		}
	}

	void Renderer::BindCameraInformation(Camera& camera, Transform& transform) {
		auto view = Inverse(transform.GetLocalMatrix());
		camera.SetAspectRatio(static_cast<float>(this->GetWidth()) / static_cast<float>(this->GetHeight()));

		this->gBufferShader->Bind();
		this->gBufferShader->SetUniform("cameraPos", transform.GetPosition());
		this->gBufferShader->SetUniform("projection", camera.GetProjectionMatrix());
		this->gBufferShader->SetUniform("view", view);

		this->lightCubeShader->Bind();
		this->lightCubeShader->SetUniform("projection", camera.GetProjectionMatrix());
		this->lightCubeShader->SetUniform("view", view);
	}

	void Renderer::DrawObject(Mesh& mesh, Material& material, Transform& transform) {
		this->gBufferShader->Bind();

		// material
		int textureCount = 0;
		if (material.DeffuseMap != nullptr) {
			glActiveTexture(GL_TEXTURE0 + textureCount);
			this->gBufferShader->SetUniform("texture_diffuse", textureCount);
			material.DeffuseMap->Bind();
			textureCount++;
		}

		if (material.SpecularMap != nullptr) {
			glActiveTexture(GL_TEXTURE0 + textureCount);
			this->gBufferShader->SetUniform("texture_specular", textureCount);
			material.SpecularMap->Bind();
			textureCount++;
		}

		// mesh
		mesh.Bind();
		this->gBufferShader->SetUniform("model", transform.GetWorldMatrix());
		glDrawElements(GL_TRIANGLES, mesh.GetIndiceCount(), GL_UNSIGNED_INT, 0);
		mesh.Unbind();
	}

	void Renderer::ApplyLight(Light& light, Transform& transform, size_t num) {
		this->lightingShader->Bind();
		this->lightingShader->SetUniform(("lights[" + std::to_string(num) + "].Position").c_str(), transform.GetPosition());
		this->lightingShader->SetUniform(("lights[" + std::to_string(num) + "].Color").c_str(), light.color);
		this->lightingShader->SetUniform(("lights[" + std::to_string(num) + "].Linear").c_str(), light.linear);
		this->lightingShader->SetUniform(("lights[" + std::to_string(num) + "].Quadratic").c_str(), light.quadratic);
	}

	void Renderer::CreateRenderQuad() {
		MeshInfo meshInfo;

		// Vertices
		std::vector<Vertex> vertices = {
			Vertex{Vector3{-1.0f,  1.0f, 0.0f}, Vector3{0.0f}, Vector2{0.0f, 1.0f}},
			Vertex{Vector3{-1.0f, -1.0f, 0.0f}, Vector3{0.0f}, Vector2{0.0f, 0.0f}},
			Vertex{Vector3{ 1.0f,  1.0f, 0.0f}, Vector3{0.0f}, Vector2{1.0f, 1.0f}},
			Vertex{Vector3{ 1.0f, -1.0f, 0.0f}, Vector3{0.0f}, Vector2{1.0f, 0.0f}},
		};
		meshInfo.vertices = vertices;

		// Indices
		std::vector<unsigned int> indices = {
			1, 0, 2,
			1, 3, 2
		};
		meshInfo.indices = indices;

		// Mesh
		this->m_renderQuad = std::make_unique<Mesh>();
		this->m_renderQuad->CreateBuffers(meshInfo);
	}

	void Renderer::CreateLightCube() {
		MeshInfo meshInfo;

		// Vertices
		std::vector<Vertex> vertices = {
			// back face
			{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f,  0.0f, -1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
			{ Vector3(1.0f,  1.0f, -1.0f), Vector3(0.0f,  0.0f, -1.0f), Vector2(1.0f, 1.0f) }, // top-right
			{ Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f,  0.0f, -1.0f), Vector2(1.0f, 0.0f) }, // bottom-right         
			{ Vector3(1.0f,  1.0f, -1.0f), Vector3(0.0f,  0.0f, -1.0f), Vector2(1.0f, 1.0f) }, // top-right
			{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f,  0.0f, -1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
			{ Vector3(-1.0f,  1.0f, -1.0f), Vector3(0.0f,  0.0f, -1.0f), Vector2(0.0f, 1.0f) }, // top-left
			// front face
			{ Vector3(-1.0f, -1.0f,  1.0f), Vector3(0.0f,  0.0f,  1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
			{ Vector3(1.0f, -1.0f,  1.0f), Vector3(0.0f,  0.0f,  1.0f), Vector2(1.0f, 0.0f) }, // bottom-right
			{ Vector3(1.0f,  1.0f,  1.0f), Vector3(0.0f,  0.0f,  1.0f), Vector2(1.0f, 1.0f) }, // top-right
			{ Vector3(1.0f,  1.0f,  1.0f), Vector3(0.0f,  0.0f,  1.0f), Vector2(1.0f, 1.0f) }, // top-right
			{ Vector3(-1.0f,  1.0f,  1.0f), Vector3(0.0f,  0.0f,  1.0f), Vector2(0.0f, 1.0f) }, // top-left
			{ Vector3(-1.0f, -1.0f,  1.0f), Vector3(0.0f,  0.0f,  1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
			// left face
			{ Vector3(-1.0f,  1.0f,  1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-right
			{ Vector3(-1.0f,  1.0f, -1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-left
			{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-left
			{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-left
			{ Vector3(-1.0f, -1.0f,  1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(0.0f, 0.0f) }, // bottom-right
			{ Vector3(-1.0f,  1.0f,  1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-right
			// right face
			{ Vector3(1.0f,  1.0f,  1.0f), Vector3(1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-left
			{ Vector3(1.0f, -1.0f, -1.0f), Vector3(1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-right
			{ Vector3(1.0f,  1.0f, -1.0f), Vector3(1.0f,  0.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-right         
			{ Vector3(1.0f, -1.0f, -1.0f), Vector3(1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-right
			{ Vector3(1.0f,  1.0f,  1.0f), Vector3(1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-left
			{ Vector3(1.0f, -1.0f,  1.0f), Vector3(1.0f,  0.0f,  0.0f), Vector2(0.0f, 0.0f) }, // bottom-left     
			// bottom face
		   { Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-right
		   { Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-left
		   { Vector3(1.0f, -1.0f,  1.0f), Vector3(0.0f, -1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-left
		   { Vector3(1.0f, -1.0f,  1.0f), Vector3(0.0f, -1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-left
		   { Vector3(-1.0f, -1.0f,  1.0f), Vector3(0.0f, -1.0f,  0.0f), Vector2(0.0f, 0.0f) }, // bottom-right
		   { Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, -1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-right
		   // top face
		  { Vector3(-1.0f,  1.0f, -1.0f), Vector3(0.0f,  1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-left
		  { Vector3(1.0f,  1.0f , 1.0f), Vector3(0.0f,  1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-right
		  { Vector3(1.0f,  1.0f, -1.0f), Vector3(0.0f,  1.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-right     
		  { Vector3(1.0f,  1.0f,  1.0f), Vector3(0.0f,  1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-right
		  { Vector3(-1.0f,  1.0f, -1.0f), Vector3(0.0f,  1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-left
		  { Vector3(-1.0f,  1.0f,  1.0f), Vector3(0.0f,  1.0f,  0.0f), Vector2(0.0f, 0.0f) }  // bottom-left
		};

		meshInfo.vertices = vertices;

		std::vector<unsigned int> indices = {0, 1, 2, 3, 4, 5};
		meshInfo.indices = indices;

		// Mesh
		this->m_lightCube = std::make_unique<Mesh>();
		this->m_lightCube->CreateBuffers(meshInfo);
	}
}
