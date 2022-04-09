#pragma once

#include "Kikurage/Core/EventHandler.h"

class WindowResizeEvent : public EventBase {
public:
	int width;
	int height;

public:
	WindowResizeEvent(int width, int height) : width(width), height(height) {}
	~WindowResizeEvent() {}
};