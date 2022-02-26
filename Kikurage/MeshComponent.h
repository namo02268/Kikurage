#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Component.h"


class MeshComponent : public Component {
public:
	Mesh mesh;
};
