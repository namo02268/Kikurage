#pragma once

#include <iostream>
#include <string>
#include <bitset>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL/Shader.h"

namespace Kikurage {
	class OpenGLWindow {
	private:
		// Window settings
		int m_width;
		int m_height;
		const char* m_title;
		GLFWwindow* m_window = nullptr;

		// Inputs
		bool anyKeyEvent = false;
		std::bitset<350> m_keyHeld;
		std::bitset<350> m_keyPressed;
		std::bitset<350> m_keyReleased;

		bool anyMouseEvent = false;
		std::bitset<8> m_mouseHeld;
		std::bitset<8> m_mousePressed;
		std::bitset<8> m_mouseReleased;
		float m_mouseScroll = 0;
		double m_cursorPos[2] = { 0, 0 };

		// Drawing
		unsigned int renderVAO, renderVBO;
		Shader* screenShader;

	public:
		OpenGLWindow(int width, int height, const char* title);
		~OpenGLWindow();

		void Draw();

		void PollEvents();
		bool IsOpen() { return !glfwWindowShouldClose(m_window); }

		GLFWwindow* GetWindowPtr() { return m_window; }

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		float GetTime() const { return (float)glfwGetTime(); }

		bool IsAnyKeyEvent() const { return anyKeyEvent; }
		bool IsKeyHeld(size_t key) const { return m_keyHeld[key]; }
		bool IsKeyPressed(size_t key) const { return m_keyPressed[key]; }
		bool IsKeyReleased(size_t key) const { return m_keyReleased[key]; }

		bool IsAnyMouseEvent() const { return anyMouseEvent; }
		bool IsMouseHeld(size_t button) const { return m_mouseHeld[button]; }
		bool IsMousePressed(size_t button) const { return m_mousePressed[button]; }
		bool IsMouseReleased(size_t button) const { return m_mouseReleased[button]; }


		void disableMouseCursor() const;
		void normalMouseCursor() const;
		const double* GetCursorPos() const { return m_cursorPos; }
		float GetMouseScroll() const { return m_mouseScroll; }
		void SetCursorPos(const float xpos, const float ypos);

	private:
		void Init();
		void Terminate();
	};
}
