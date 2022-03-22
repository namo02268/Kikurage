#pragma once

#include "OpenGL/Window.h"

class SceneWindow : public Window {
public:
	SceneWindow(int width, int height, const char* title);
	~SceneWindow() = default;

	void draw(unsigned int renderTexture);
};