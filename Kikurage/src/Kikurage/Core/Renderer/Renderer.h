#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderBuffer.h"
#include "Kikurage/Events/WindowResizeEvent.h"
#include "Kikurage/Core/Renderer/BaseCamera.h"

struct RenderBuffers {
	Texture2D renderTexture;
	FrameBuffer framebuffer;
	RenderBuffer renderbuffer;

	void Init(int width, int height);
	void Resize(int width, int height);
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

	void ResizeBuffers(int width, int height);
	void ListenWindowResizeEvent(WindowResizeEvent* event);

	void BindFBO();
	void UnbindFBO();

	void AddShader(Shader* shader) { m_shaders.push_back(shader); }
	void BindCameraInformation(BaseCamera* camera, const TransformComponent* transform);

	Texture2D& GetRenderTexture() { return this->renderBuffers->renderTexture; }
	unsigned int GetWidth() const { return this->m_renderSettings.width; }
	unsigned int GetHeight() const { return this->m_renderSettings.height; }

	struct RenderSettings {
		float width = 0;
		float height = 0;
	};

	RenderSettings m_renderSettings;
};