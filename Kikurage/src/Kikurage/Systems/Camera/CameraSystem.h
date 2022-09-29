#pragma once

#include "Kikurage/ECS/System.h"
#include "Kikurage/Core/Window.h"
#include "OpenGL//Shader.h"
#include <GLFW/glfw3.h>

#include "Kikurage/Core/Renderer/EditorCamera.h"

class CameraSystem : public System {
private:
	EditorCamera camera;

public:
	CameraSystem();
	~CameraSystem();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
};
