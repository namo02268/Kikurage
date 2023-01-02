#pragma once
#include <glm/glm.hpp>

namespace Kikurage {
	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
	};
}
