#pragma once

#include "Kikurage/Core/Window.h"
#include "OpenGL/Texture2D.h"

class SceneEditor : public Window {
public:
	SceneEditor(int width, int height, const char* title);
	~SceneEditor() = default;

	void Draw(Texture2D& renderTexture) override;

	void disableMouseCursor() const override;
	void normalMouseCursor() const override;
};