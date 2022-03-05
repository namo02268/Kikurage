#pragma once

#include "Component.h"
#include "System.h"
#include "Window.h"
#include "Shader.h"

class CameraSystem : public System {
private:
	Window* m_window;
	Shader m_shader;

	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouse = true;

public:
	CameraSystem(Window* window, Shader shader);
	~CameraSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};
