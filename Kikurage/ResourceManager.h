#pragma once

#include <map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

class ResourceManager {
public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Mesh> Meshes;

	//------------------------Shader------------------------//
	// loads a shader program from file
	static void LoadShaderFromFile(const char* vShdaerFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// retrieves a stored shader
	static Shader GetShader(std::string name);

	//-------------------------Model-------------------------//
	// load a mesh form file
	static void LoadMeshFromFile(const char* modelFile, std::string name);

	// retrieves a stored mesh
	static Mesh GetMesh(std::string name);

	//------------------------Texture------------------------//

	//-------------------------Utils-------------------------//
	// properly de-allocates all loaded resources
	static void Clear();

private:
	ResourceManager() {}

	//------------------------Shader------------------------//
	// loads and generates a shader from file
	static Shader loadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile, const char* geomShaderFile = nullptr);

	//-------------------------Model-------------------------//
	static void processNode(aiNode* node, const aiScene* scene, Mesh& mesh);

	static void processMesh(aiMesh* aimesh, const aiScene* scene, Mesh& mesh);
};