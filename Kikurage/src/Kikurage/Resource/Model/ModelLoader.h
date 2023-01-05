#pragma once

#include "Kikurage/Resource/Model/ModelInfo.h"
#include "Kikurage/ECS/Entity.h"

namespace Kikurage {
	class ModelLoader {
	public:
		static void LoadEntity(const char* path, float size);
		static ModelInfo LoadFromFile(const char* path);
		static void GenerateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	};
}
