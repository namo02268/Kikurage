#pragma once

#include "Kikurage/Core/Application.h"

class Event {
public:
	template<typename EventType>
	static void publish(EventType* event) {
		Application::GetInstance().GetEventHandler().publish(event);
	}

	template<typename T, typename EventType>
	static void subscribe(T* instance, void (T::* memberFunction)(EventType*)) {
		Application::GetInstance().GetEventHandler().subscribe(instance, memberFunction);
	}
};