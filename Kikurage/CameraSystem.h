#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "System.h"
#include "Shader.h"
#include "Window.h"

class CameraSystem : public System {
private:
	Shader m_shader;
	float m_width;
	float m_height;
	Window* m_window;

public:
	CameraSystem(Shader shader, Window* window);
	~CameraSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};