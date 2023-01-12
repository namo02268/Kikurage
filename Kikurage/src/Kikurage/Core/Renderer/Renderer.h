#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Kikurage/ECS/Entity.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderBuffer.h"
#include "Kikurage/Core/Renderer/BaseCamera.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Mesh/Mesh.h"

namespace Kikurage {
	struct RenderBuffers {
		Texture2D renderTexture;
		FrameBuffer framebuffer;
		RenderBuffer renderbuffer;

		void Init();
		void Resize(unsigned int width, unsigned int height);
	};

	struct GBuffers {
		FrameBuffer gBuffer;
		Texture2D Position;
		Texture2D Normal;
		Texture2D Albedo;
		Texture2D Specular;
		RenderBuffer renderbuffer;

		void Init();
		void Resize(unsigned int width, unsigned int height);
	};

	class Renderer {
	private:
		std::unique_ptr<RenderBuffers> renderBuffers = std::make_unique<RenderBuffers>();
		std::unique_ptr<GBuffers> gBuffers = std::make_unique<GBuffers>();
		std::vector<Shader*> m_shaders;

	public:
		bool IsDefaultFboEnable = true;

	public:
		Renderer();
		virtual ~Renderer();

		void Init();
		void Start();
		void End();

		void ResizeViewport();

		void BindFBO();
		void UnbindFBO();

		void AddShader(Shader* shader) { m_shaders.push_back(shader); }
		void BindCameraInformation(BaseCamera& camera, Transform& transform);

		void DrawObject(Mesh* mesh);

		Texture2D& GetRenderTexture() { return this->renderBuffers->renderTexture; }
		Texture2D& GetPositionTexture() { return this->gBuffers->Position; }
		Texture2D& GetNormalTexture() { return this->gBuffers->Normal; }
		Texture2D& GetAlbedoTexture() { return this->gBuffers->Albedo; }
		Texture2D& GetSpecularTexture() { return this->gBuffers->Specular; }
		unsigned int GetWidth() const { return this->m_renderInfo.width; }

		unsigned int GetHeight() const { return this->m_renderInfo.height; }
		void SetWidth(const unsigned int width) { this->m_renderInfo.width = width; }
		void SetHeight(const unsigned int height) { this->m_renderInfo.height = height; }

		struct RenderInfo {
			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int lastWidth = 0;
			unsigned int lastHeight = 0;
		};

		RenderInfo m_renderInfo;
	};
}
