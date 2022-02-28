#pragma once

#include <iostream>
#include <string>
#include <bitset>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	int m_width;
	int m_height;
	const char* m_title;
	GLFWwindow* m_window = nullptr;

	mutable std::bitset<350> m_keyHeld;
	mutable std::bitset<350> m_keyPressed;
	mutable std::bitset<350> m_keyReleased;

public:
	Window(int width, int height, const char* title);
	~Window();

	void Clear();
	void Update();
	bool Closed() { return glfwWindowShouldClose(m_window); }

	GLFWwindow* GetWindow() { return m_window; }
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	void SetWidth(int width) { m_width = width; }
	void SetHeight(int height) { m_height = height; }
	bool IsKeyHeld(size_t key) const { return m_keyHeld[key]; }
	bool IsKeyPressed(size_t key) const { return m_keyPressed[key]; }
	bool IsKeyReleased(size_t key) const {return m_keyReleased[key]; }

private:
	void Init();
	void Terminate();
};
