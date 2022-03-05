#pragma once

#include <iostream>
#include <string>
#include <bitset>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
private:
	int m_width;
	int m_height;
	const char* m_title;
	GLFWwindow* m_window = nullptr;

	bool anyKeyEvent = false;
	bool anyMouseEvent = false;
	std::bitset<350> m_keyHeld;
	std::bitset<350> m_keyPressed;
	std::bitset<350> m_keyReleased;
	std::bitset<8> m_mouseHeld;
	std::bitset<8> m_mousePressed;
	std::bitset<8> m_mouseReleased;

	float m_mouseScroll = 0;

public:
	Window(int width, int height, const char* title);
	~Window();

	void Clear();
	void Update();
	bool Closed() { return glfwWindowShouldClose(m_window); }

	GLFWwindow* GetWindow() { return m_window; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	bool IsAnyKeyEvent() const { return anyKeyEvent; }
	bool IsKeyHeld(size_t key) const { return m_keyHeld[key]; }
	bool IsKeyPressed(size_t key) const { return m_keyPressed[key]; }
	bool IsKeyReleased(size_t key) const { return m_keyReleased[key]; }

	bool IsAnyMouseEvent() const { return anyMouseEvent; }
	bool IsMouseHeld(size_t button) const { return m_mouseHeld[button]; }
	bool IsMousePressed(size_t button) const { return m_mousePressed[button]; }
	bool IsMouseReleased(size_t button) const { return m_mouseReleased[button]; }
	glm::vec2 GetCursorPosition() const;
	void disableMouseCursor() const;
	void normalMouseCursor() const;

	float GetMouseScroll() const { return m_mouseScroll; }

	float GetTime() const { return (float)glfwGetTime(); }

private:
	void Init();
	void Terminate();
};