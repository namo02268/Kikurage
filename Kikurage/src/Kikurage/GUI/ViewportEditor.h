#pragma once

#include "Kikurage/Core/Window.h"

class ViewportEditor : public Window {
public:
	ViewportEditor(int width, int height, const char* title);
	~ViewportEditor() = default;

	void Draw() override;

	void disableMouseCursor() const override;
	void normalMouseCursor() const override;
};