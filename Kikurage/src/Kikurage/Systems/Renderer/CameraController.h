#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "Kikurage/Systems/Renderer/PerspectiveCamera.h"
#include "Kikurage/Events/WindowResizeEvent.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderBuffer.h"

struct CameraBuffers {
	Texture2D renderTexture;
	FrameBuffer framebuffer;
	RenderBuffer renderbuffer;

	void Init(int width, int height);
	void Resize(int width, int height);
};

class CameraController {
private:
	std::unique_ptr<CameraBuffers> cameraBuffers = std::make_unique<CameraBuffers>();
	PerspectiveCamera camera;
	bool renderingEnabled = true;

public:
	CameraController();
	~CameraController() = default;

	// Event listner(window size)
	void CameraInputUpdate();
	void Resize(int width, int height);
	void ListenWindowResizeEvent(WindowResizeEvent* event);

//	void SetRenderTexture(const Texture2D& texture);
	Texture2D& GetRenderTexture() const { return cameraBuffers->renderTexture; }

	glm::mat4 getProjectionMatrix() const { return camera.projection; }
	glm::mat4 getViewMatrix() const { return camera.view; }
};

// set camera position to shader
// DrawObjects(){ DrawObject(); }