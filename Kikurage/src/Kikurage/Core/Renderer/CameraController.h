#pragma once

#include <glm/glm.hpp>

#include "Kikurage/Core/Renderer/PerspectiveCamera.h"
#include "Kikurage/Events/WindowResizeEvent.h"
#include "OpenGL/Shader.h"

class CameraController {
private:
	PerspectiveCamera mainCamera;
	bool renderingEnabled = true;
	std::vector<Shader*> m_shaders;

public:
	CameraController();
	~CameraController() = default;

	void CameraInputUpdate();

//	void SetRenderTexture(const Texture2D& texture);
	void SetShader(Shader* shader);
	void RemoveShader(Shader* shader);

	glm::mat4 GetProjectionMatrix() const { return mainCamera.projection; }
	glm::mat4 GetViewMatrix() const { return mainCamera.view; }

private:
};

// set camera position to shader
// DrawObjects(){ DrawObject(); }