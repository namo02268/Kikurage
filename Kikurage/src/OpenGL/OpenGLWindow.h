#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "OpenGL/Window.h"

class OpenGLWindow : public Window
{
private:
	GLFWwindow* m_window = nullptr;

	// Render FBO & Texture
	unsigned int framebuffer;
	unsigned int textureColorbuffer;

public:
	OpenGLWindow(int width, int height, const char* title);
	~OpenGLWindow();

	void BindFBO() { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); }
	void UnbindFBO() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	unsigned int getRenderTexture() { return textureColorbuffer; }

	void Clear();
	void Update();
	bool Closed() { return glfwWindowShouldClose(m_window); }

	GLFWwindow* GetWindow() { return m_window; }


	float GetTime() const { return (float)glfwGetTime(); }

	void disableMouseCursor() const;
	void normalMouseCursor() const;
	float GetMouseScroll() const { return m_mouseScroll; }


private:
	void Init();
	void Terminate();

	void MakeFBO();
};