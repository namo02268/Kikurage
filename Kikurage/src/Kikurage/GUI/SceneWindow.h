#pragma once

#include "Kikurage/Core/Window.h"
#include "Kikurage/Resource/Texture/Texture2D.h"

class SceneWindow : public Window {
public:
	SceneWindow(int width, int height, const char* title);
	~SceneWindow() = default;

	void Draw(Texture2D* renderTexture) override;

	void disableMouseCursor() const override;
	void normalMouseCursor() const override;
};