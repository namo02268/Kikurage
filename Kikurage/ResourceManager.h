#pragma once

#include <map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"

enum class TextureType {
	RGB,
	RGBA,
	HDR
};

class ResourceManager {
public:
	// resource storage
	static std::map<std::string, std::unique_ptr<Shader>> Shaders;
	static std::map<std::string, Texture2D> Textures;
	static std::map<std::string, Mesh> Meshes;

	//------------------------Shader------------------------//
	// loads a shader program from file
	static void LoadShaderFromFile(const char* vShdaerFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// retrieves a stored shader
	static Shader* GetShader(std::string name);

	//-------------------------Model-------------------------//
	// load a mesh form file
	static void LoadMeshFromFile(const char* modelFile, std::string name);

	// retrieves a stored mesh
	static Mesh GetMesh(std::string name);

	//------------------------Texture------------------------//
		// loads a texture from file
	static void LoadTexture(const char* file, TextureType type, std::string name);

	// retrieves a stored texture
	static Texture2D GetTexture(std::string name);

	//-------------------------Utils-------------------------//
	// properly de-allocates all loaded resources
	static void Clear();

private:
	ResourceManager() {}

	//------------------------Texture------------------------//
	// loads a single texture from file
	static Texture2D loadTextureFromFile(const char* file, TextureType type);

	//-------------------------Model-------------------------//
	static void processNode(aiNode* node, const aiScene* scene, Mesh& mesh);

	static void processMesh(aiMesh* aimesh, const aiScene* scene, Mesh& mesh);
};