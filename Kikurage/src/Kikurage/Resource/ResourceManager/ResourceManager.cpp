#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image/stb_image.h"

namespace Kikurage {
    //------------------------Shader------------------------//
    Shader* ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        try
        {
            std::ifstream vertexShaderFile(vShaderFile);
            std::ifstream fragmentShaderFile(fShaderFile);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vertexShaderFile.rdbuf();
            fShaderStream << fragmentShaderFile.rdbuf();
            vertexShaderFile.close();
            fragmentShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

            if (gShaderFile != nullptr)
            {
                std::ifstream geometryShaderFile(gShaderFile);
                std::stringstream gShaderStream;
                gShaderStream << geometryShaderFile.rdbuf();
                geometryShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::exception e)
        {
            std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        const char* gShaderCode = geometryCode.c_str();

        auto shader = std::make_shared<Shader>();
        shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
        Shaders[name] = std::move(shader);

        return Shaders[name].get();
    }

    Shader* ResourceManager::GetShader(std::string name) {
        return Shaders[name].get();
    }

    //------------------------Texture------------------------//
    Texture2D* ResourceManager::LoadTexture(const char* file, TextureType type, std::string name) {
        for (auto& texture : Textures) {
            if (strcmp(texture.second->GetFilepath(), file) == 0) {
                std::cout << file << " is already loaded." << std::endl;
                return texture.second.get();
            }
        }

        // create texture object
        auto texture = std::make_shared<Texture2D>();
        auto format = GL_RGB;
        if (type == TextureType::RGB) {
            format = GL_RGB;
        }
        if (type == TextureType::RGBA) {
            format = GL_RGBA;
        }
        if (type == TextureType::HDR) {
            format = GL_RGB16F;
            texture->SetWrapType(GL_CLAMP_TO_EDGE);
        }

        texture->SetFilepath(file);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
        texture->Generate(data, width, height, nrChannels, format);
        stbi_image_free(data);

        Textures[name] = std::move(texture);
        return Textures[name].get();
    }

    Texture2D* ResourceManager::GetTexture(std::string name) {
        return Textures[name].get();
    }
}
