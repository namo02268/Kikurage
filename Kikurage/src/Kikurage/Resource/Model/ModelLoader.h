#pragma once

#include "Kikurage/Resource/Model/ModelInfo.h"
#include "Kikurage/Core/ECS/ECS.h"

namespace Kikurage {
	class ModelLoader {
	public:
		static Nameko::Entity LoadEntity(const char* path, float size);
		static ModelInfo LoadFromFile(const char* path);
		static void GenerateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	};
}
