#pragma once

#include <bitset>
#include "OpenGL/Texture2D.h"

class Window {
protected:
	// Window settings
	int m_width;
	int m_height;
	const char* m_title;

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


public:
	virtual ~Window() = default;

	virtual void Draw() = 0;

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
	virtual float GetMouseScroll() const { return 0; }
	const double* GetCursorPos() const { return m_cursorPos; }
	virtual void SetCursorPos(const float xpos, const float ypos) {}
	virtual void disableMouseCursor() const {}
	virtual void normalMouseCursor() const {}
};