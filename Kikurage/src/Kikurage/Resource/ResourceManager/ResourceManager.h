#pragma once

#include <unordered_map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Utils/Singleton.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"
#include "Kikurage/Resource/Model/Model.h"

namespace Kikurage {
	// TODO : move to Texture.h
	enum class TextureType {
		RGB,
		RGBA,
		HDR
	};

	class ResourceManager : public Singleton<ResourceManager> {
	private:
		// resource storage
		std::unordered_map<std::string, std::unique_ptr<Shader>> Shaders;
		std::unordered_map<std::string, std::unique_ptr<Texture2D>> Textures;
		std::unordered_map<std::string, std::unique_ptr<Model>> Models;

	protected:
		ResourceManager();
		virtual ~ResourceManager();

	public:
		friend class Singleton<ResourceManager>;

		//------------------------Shader------------------------//
		// loads a shader program from file
		void LoadShader(const char* vShdaerFile, const char* fShaderFile, const char* gShaderFile, std::string name);

		// retrieves a stored shader
		Shader* GetShader(std::string name);

		//-------------------------Model-------------------------//
		// load a mesh form file
		void LoadModel(const char* modelFile, std::string name);

		// retrieves a stored mesh
		Model* GetModel(std::string name);

		//------------------------Texture------------------------//
			// loads a texture from file
		void LoadTexture(const char* file, TextureType type, std::string name);

		// retrieves a stored texture
		Texture2D* GetTexture(std::string name);

		//-------------------------Utils-------------------------//
		// properly de-allocates all loaded resources
		void Clear();
	};
}
