#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Kikurage/Core/Window.h"
#include "OpenGL/Shader.h"

class OpenGLWindow : public Window
{
private:
	GLFWwindow* m_window = nullptr;
	
	unsigned int renderVAO, renderVBO;
	Shader* screenShader;

public:
	OpenGLWindow(int width, int height, const char* title);
	~OpenGLWindow();

	void Draw(Texture2D* renderTexture) override;

	void Clear();
	void Update();
	bool IsOpen() { return !glfwWindowShouldClose(m_window); }

	GLFWwindow* GetWindow() { return m_window; }

	float GetTime() const { return (float)glfwGetTime(); }

	void disableMouseCursor() const override;
	void normalMouseCursor() const override;
	float GetMouseScroll() const { return m_mouseScroll; }

private:
	void Init();
	void Terminate();
};

