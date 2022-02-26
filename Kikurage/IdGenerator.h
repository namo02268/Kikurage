#pragma once

#include "Defs.h"

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
