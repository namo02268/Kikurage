#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image/stb_image.h"

std::map<std::string, std::unique_ptr<Shader>> ResourceManager::Shaders;
std::map<std::string, std::unique_ptr<Texture2D>> ResourceManager::Textures;
std::map<std::string, std::unique_ptr<Mesh>> ResourceManager::Meshes;

// TODO: template‰»

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
    if (type == TextureType::RGB) {
        texture->Internal_Format = GL_RGB;
        texture->Image_Format = GL_RGB;
    }
    if (type == TextureType::RGBA) {
        texture->Internal_Format = GL_RGBA;
        texture->Image_Format = GL_RGBA;
    }
    if (type == TextureType::HDR) {
        texture->Internal_Format = GL_RGB16F;
        texture->Image_Format = GL_RGB;
        texture->Wrap_S = GL_CLAMP_TO_EDGE;
        texture->Wrap_T = GL_CLAMP_TO_EDGE;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture->Generate(width, height, data);
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
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // process ASSIMP's root node recursively(Ä‹A“I)
    Mesh* mesh = new Mesh();
    processNode(scene->mRootNode, scene, mesh);

    std::unique_ptr<Mesh> Uptr(mesh);
    Meshes[name] = std::move(Uptr);
}

Mesh* ResourceManager::GetMesh(std::string name)
{
    return Meshes[name].get();
}

void ResourceManager::processNode(aiNode* node, const aiScene* scene, Mesh* mesh) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(aimesh, scene, mesh);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, mesh);
    }
}

void ResourceManager::processMesh(aiMesh* aimesh, const aiScene* scene, Mesh* mesh) {
    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < aimesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;

        // positions
        vector.x = aimesh->mVertices[i].x;
        vector.y = aimesh->mVertices[i].y;
        vector.z = aimesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (aimesh->HasNormals()) {
            vector.x = aimesh->mNormals[i].x;
            vector.y = aimesh->mNormals[i].y;
            vector.z = aimesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coords
        if (aimesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = aimesh->mTextureCoords[0][i].x;
            vec.y = aimesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f);
        }

        mesh->vertices.push_back(vertex);
    }

    // walk through each of the mesh's face
    for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
        aiFace face = aimesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            mesh->indices.push_back(face.mIndices[j]);
    }
}


//-------------------------Utils-------------------------//
void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto& iter : Shaders)
        glDeleteProgram(iter.second->ID);
}