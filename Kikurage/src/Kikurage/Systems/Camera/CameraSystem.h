#pragma once

#include "Kikurage/ECS/System.h"
#include "Kikurage/Core/Window.h"
#include "Kikurage/Resource/Shader/Shader.h"
#include <GLFW/glfw3.h>

class CameraSystem : public System {
private:
	Window* m_window;
	std::vector<Shader*> m_shaders;

	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouse = true;

public:
	CameraSystem(Window* window);
	~CameraSystem();

	void addShader(Shader* shader);

	void init() override;
	void update(float dt) override;
	void draw() override;
};
