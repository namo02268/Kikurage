#include "Kikurage/Resource/Model/Model.h"

namespace Kikurage {
	void Model::Load(const char* path) {
		ModelInfo modelInfo = ModelLoader::LoadFromFile(path);
		for (auto& meshInfo : modelInfo.meshes) {
			Mesh mesh;
			mesh.CreateBuffers(meshInfo);
			this->meshes.push_back(std::move(mesh));
		}
	}
}
