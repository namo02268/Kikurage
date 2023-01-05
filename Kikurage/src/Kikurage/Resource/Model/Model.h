#pragma once

#include <vector>
#include "Kikurage/Resource/Mesh/Mesh.h"
#include "Kikurage/Resource/Model/ModelLoader.h"

namespace Kikurage {
	class Model {
		friend class ModelLoader;

	private:
		std::vector<Mesh> meshes;

	public:
		Model() {}
		~Model() {}

		void Load(const char* path);

		const std::vector<Mesh>* GetMeshes() { return &this->meshes; }
	};
}
