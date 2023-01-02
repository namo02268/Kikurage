#pragma once

#include "Kikurage/ECS/ECS_def.h"

namespace Kikurage {
	inline EntityID getEntityID() {
		static EntityID entityID = 1;
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
}
