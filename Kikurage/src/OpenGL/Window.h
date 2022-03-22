#pragma once

#include <bitset>

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
	const double* GetCursorPos() const { return m_cursorPos; }
};