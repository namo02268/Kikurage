#pragma once

#include <typeindex>
#include <typeinfo>
#include "Kikurage/ECS/ECS_def.h"

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