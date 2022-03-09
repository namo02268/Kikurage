#pragma once

#include "System.h"
#include "Window.h"

class GUI : public System {
private:
	Window* parentWindow;
	
public:
	GUI(Window* window);
	~GUI();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

