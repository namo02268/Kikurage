#pragma once

#include <typeindex>
#include <typeinfo>
#include "ECS/ECS_def.h"

inline EntityID getEntityID() {
	static EntityID entityID = 0;
	return entityID++;
}

inline ComponentTypeID getComponentTypeID() {
	static ComponentTypeID componentID = 0;
	return componentID++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept {
	static ComponentTypeID typeID = getComponentTypeID();
	return typeID;
}

inline EventTypeID getEventTypeID() {
	static EventTypeID eventID = 0;
	return eventID++;
}

template <typename T> inline EventTypeID getEventTypeID() noexcept {
	static EventTypeID typeID = getEventTypeID();
	return typeID;
}