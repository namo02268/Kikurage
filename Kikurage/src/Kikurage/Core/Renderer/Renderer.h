#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Nameko/Entity.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderBuffer.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Camera/Camera.h"
#include "Kikurage/Components/Mesh/Mesh.h"
#include "Kikurage/Components/Material/Material.h"
#include "Kikurage/Components/Light/Light.h"

namespace Kikurage {
	struct RenderBuffers
	{
		Texture2D renderTexture;
		FrameBuffer framebuffer;
		RenderBuffer renderbuffer;

		void Init();
		void Resize(unsigned int width, unsigned int height);
	};

	struct GBuffers
	{
		FrameBuffer gBuffer;
		Texture2D Position;
		Texture2D Normal;
		Texture2D Albedo;
		Texture2D Specular;
		RenderBuffer renderbuffer;

		void Init();
		void Resize(unsigned int width, unsigned int height);
	};

	class Renderer
	{
	private:
		std::unique_ptr<RenderBuffers> renderBuffers = std::make_unique<RenderBuffers>();
		std::unique_ptr<GBuffers> gBuffers = std::make_unique<GBuffers>();
		Shader* gBufferShader = nullptr;
		Shader* lightingShader = nullptr;
		Shader* lightCubeShader = nullptr;
		std::unique_ptr<Mesh> m_renderQuad;
		std::unique_ptr<Mesh> m_lightCube;

	public:
		bool IsDefaultFboEnable = true;

	public:
		Renderer();
		virtual ~Renderer();

		void Init();

		void StartPipeLine();
		void GeometryPass();
		void LightingPass();
		void EndPipeLine();

		void ResizeViewport();

		void BindCameraInformation(Camera& camera, Transform& transform);

		void DrawObject(Mesh& mesh, Material& material, Transform& transform);
		void ApplyLight(Light& light, Transform& transform, size_t num);

		Texture2D& GetRenderTexture() const { return this->renderBuffers->renderTexture; }
		Texture2D& GetPositionTexture() const { return this->gBuffers->Position; }
		Texture2D& GetNormalTexture() const { return this->gBuffers->Normal; }
		Texture2D& GetAlbedoTexture() const { return this->gBuffers->Albedo; }
		Texture2D& GetSpecularTexture() const { return this->gBuffers->Specular; }
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

	private:
		// TODO : Primitive.h
		void CreateRenderQuad();
		void CreateLightCube();
	};
}
