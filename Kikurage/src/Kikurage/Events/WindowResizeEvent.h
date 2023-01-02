#pragma once

#include "Kikurage/Events/EventBase.h"

namespace Kikurage {
	struct WindowResizeEvent : public EventBase {
	public:
		int width;
		int height;

	public:
		WindowResizeEvent(int width, int height) : width(width), height(height) {}
		~WindowResizeEvent() {}
	};
}
