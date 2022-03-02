#pragma once

#include "System.h"
#include "Window.h"

class InputSystem : public System {
private:
	Window* m_window;

public:
	InputSystem(Window* window);
	~InputSystem();

	void init() override;
	void update(float dt) override;
	void draw() override;
};