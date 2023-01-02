#include "Kikurage/Resource/ResourceManager/ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image/stb_image.h"

namespace Kikurage {
    ResourceManager::ResourceManager() {

    }

    ResourceManager::~ResourceManager() {
        this->Clear();
    }

    //------------------------Shader------------------------//
    void ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        try
        {
            // open files
            std::ifstream vertexShaderFile(vShaderFile);
            std::ifstream fragmentShaderFile(fShaderFile);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vertexShaderFile.rdbuf();
            fShaderStream << fragmentShaderFile.rdbuf();
            // close file handlers
            vertexShaderFile.close();
            fragmentShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            // if geometry shader path is present, also load a geometry shader
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
        // 2. now create shader object from source code
        auto shader = std::make_unique<Shader>();
        shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
        Shaders[name] = std::move(shader);
    }

    Shader* ResourceManager::GetShader(std::string name)
    {
        return Shaders[name].get();
    }

    //------------------------Texture------------------------//
    void ResourceManager::LoadTexture(const char* file, TextureType type, std::string name)
    {
        // create texture object
        auto texture = std::make_unique<Texture2D>();
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

        // load image
        int width, height, nrChannels;
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
        // now generate texture
        texture->Generate(data, width, height, nrChannels, format);
        // and finally free image data
        stbi_image_free(data);

        Textures[name] = std::move(texture);
    }

    Texture2D* ResourceManager::GetTexture(std::string name)
    {
        return Textures[name].get();
    }

    //------------------------Model------------------------//
    void ResourceManager::LoadMeshFromFile(const char* modelFile, std::string name) {
        auto Uptr = std::make_unique<Mesh>();
        Uptr->LoadFromFile(modelFile);
        Meshes[name] = std::move(Uptr);
    }

    Mesh* ResourceManager::GetMesh(std::string name) {
        return Meshes[name].get();
    }


    //-------------------------Utils-------------------------//
    void ResourceManager::Clear()
    {
    }
}
