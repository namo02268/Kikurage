#pragma once

#include <unordered_map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Utils/Singleton.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"

namespace Kikurage {
	// TODO : move to Texture.h
	enum class TextureType {
		RGB,
		RGBA,
		HDR
	};

	class ResourceManager {
	private:
		// resource storage
		inline static std::unordered_map<std::string, std::shared_ptr<Shader>> Shaders;
		inline static std::unordered_map<std::string, std::shared_ptr<Texture2D>> Textures;

	private:
		ResourceManager() = default;
		~ResourceManager() = default;

	public:
		static Shader* LoadShader(const char* vShdaerFile, const char* fShaderFile, const char* gShaderFile, std::string name);
		static Shader* GetShader(std::string name);

		static Texture2D* LoadTexture(const char* file, TextureType type, std::string name);
		static Texture2D* GetTexture(std::string name);
	};
}
