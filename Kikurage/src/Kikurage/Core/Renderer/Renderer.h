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


	class Renderer {
	private:
		std::unique_ptr<RenderBuffers> renderBuffers = std::make_unique<RenderBuffers>();
		std::vector<Shader*> m_shaders;

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
		unsigned int GetWidth() const { return this->m_renderInfo.width; }
		unsigned int GetHeight() const { return this->m_renderInfo.height; }

		struct RenderInfo {
			unsigned int width = 0;
			unsigned int height = 0;
		};

		RenderInfo m_renderInfo;
	};
}
