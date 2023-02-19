#include "Kikurage/Systems/AABBCollision/AABBCollision.h"

#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Mesh/Mesh.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Kikurage/Core/Event.h"

namespace Kikurage {
	AABBCollision::AABBCollision() {
	}

	AABBCollision::~AABBCollision() {
	}

	void AABBCollision::Init() {
	}

	void AABBCollision::Update(float dt) {
	}

	void AABBCollision::Draw() {

	}

	bool AABBCollision::intersect(AABB& a, AABB& b) {
		return (a.Min.x <= b.Max.x && a.Max.x >= b.Min.x) &&
			(a.Min.y <= b.Max.y && a.Max.y >= b.Min.y) &&
			(a.Min.z <= b.Max.z && a.Max.z >= b.Min.z);
	}
}
