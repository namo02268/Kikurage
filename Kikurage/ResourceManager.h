#pragma once

#include <map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager {
public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	//------------------------Shader------------------------//
	// loads a shader program from file
	static Shader LoadShaderFromFile(const char* vShdaerFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// retrieves a stored shader
	static Shader GetShader(std::string name);

	//------------------------Texture------------------------//
	// loads a texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);

	// retrieves a stored texture
	static Texture2D GetTexture(std::string name);

	//-------------------------Utils-------------------------//
	// properly de-allocates all loaded resources
	static void Clear();

private:
	ResourceManager() {}

	//------------------------Shader------------------------//
	// loads and generates a shader from file
	static Shader loadShaderFromFile(const char* vertShaderFile, const char* fragShaderFile, const char* geomShaderFile = nullptr);

	//------------------------Texture------------------------//
	// loads a single texture from file
	static Texture2D loadTextureFromFile(const char* file, bool alpha);

};