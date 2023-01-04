#include "Kikurage/Systems/Transform/TransformUpdator.h"

#include "Kikurage/ECS/ECS.h"
#include "Kikurage/Components/Transform.h"

#include "glm/gtx/transform.hpp"

namespace Kikurage {
	TransformUpdator::TransformUpdator() {
		auto family = getComponentTypeID<Transform>();
		m_requiredComponent[family] = true;
		family = getComponentTypeID<Relationship>();
		m_requiredComponent[family] = true;
	}

	void TransformUpdator::Init() {

	}

	void TransformUpdator::Update(float dt) {
	}

	void TransformUpdator::Draw() {

	}
}
