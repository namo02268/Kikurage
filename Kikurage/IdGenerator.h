#pragma once

#include "ECS_def.h"
#include <typeindex>
#include <typeinfo>

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