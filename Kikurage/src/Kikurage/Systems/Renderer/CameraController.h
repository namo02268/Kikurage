#pragma once

#include <glm/glm.hpp>

#include "Kikurage/Systems/Renderer/PerspectiveCamera.h"
#include "Kikurage/Events/WindowResizeEvent.h"

class CameraController {
private:
	PerspectiveCamera camera;
	bool renderingEnabled = true;

public:
	CameraController();
	~CameraController() = default;

	void CameraInputUpdate();

//	void SetRenderTexture(const Texture2D& texture);

	glm::mat4 getProjectionMatrix() const { return camera.projection; }
	glm::mat4 getViewMatrix() const { return camera.view; }
};

// set camera position to shader
// DrawObjects(){ DrawObject(); }