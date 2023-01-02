#include "Kikurage/Resource/Mesh/MeshLoader.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Utils/Math.h"

namespace Kikurage {
    // TODO : move to math.h
    std::pair<glm::vec3, glm::vec3> MinMaxVector(glm::vec3* vertices, size_t size);

    ObjectInfo MeshLoader::LoadFromFile(const char* path) {
        ObjectInfo object;

        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return object;
        }

        object.meshes.resize((size_t)scene->mNumMeshes);

        std::cout << "Meshes : " << scene->mNumMeshes << std::endl;
        std::cout << "materials : " << scene->mNumMaterials << std::endl;

        for (size_t i = 0; i < (size_t)scene->mNumMeshes; ++i) {
            auto& mesh = scene->mMeshes[i];
            auto& meshInfo = object.meshes[i];

            meshInfo.name = mesh->mName.C_Str();
            meshInfo.hasNormals = mesh->HasNormals();
            meshInfo.hasTextureCoords = mesh->HasTextureCoords(0);

            // vertices
            meshInfo.vertices.resize((size_t)mesh->mNumVertices);
            for (size_t i = 0; i < (size_t)mesh->mNumVertices; ++i) {
                meshInfo.vertices[i].Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
                meshInfo.vertices[i].Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

                if (meshInfo.hasTextureCoords) {
                    meshInfo.vertices[i].TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
                }
            }

            // aabb
            float MinX = std::numeric_limits<float>::max();
            float MaxX = -std::numeric_limits<float>::max();
            float MinY = std::numeric_limits<float>::max();
            float MaxY = -std::numeric_limits<float>::max();
            float MinZ = std::numeric_limits<float>::max();
            float MaxZ = -std::numeric_limits<float>::max();

            for (size_t i = 0; i < (size_t)mesh->mNumVertices; ++i) {
                MinX = std::min(mesh->mVertices[i].x, MinX);
                MaxX = std::max(mesh->mVertices[i].x, MaxX);
                MinY = std::min(mesh->mVertices[i].y, MinY);
                MaxY = std::max(mesh->mVertices[i].y, MaxY);
                MinZ = std::min(mesh->mVertices[i].z, MinZ);
                MaxZ = std::max(mesh->mVertices[i].z, MaxZ);
            }

            meshInfo.aabb = { glm::vec3(MinX, MinY, MinZ), glm::vec3(MaxX, MaxY, MaxZ) };

            // indices
            meshInfo.indices.resize((size_t)mesh->mNumFaces * 3);
            for (size_t i = 0; i < (size_t)mesh->mNumFaces; ++i) {
                if (mesh->mFaces[i].mNumIndices == 3) {
                    meshInfo.indices[3 * i + 0] = mesh->mFaces[i].mIndices[0];
                    meshInfo.indices[3 * i + 1] = mesh->mFaces[i].mIndices[1];
                    meshInfo.indices[3 * i + 2] = mesh->mFaces[i].mIndices[2];
                }
            }
        }
        return object;
    }

    void MeshLoader::GenerateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        for (auto& vertex : vertices) {
            vertex.Normal = glm::vec3(0.0f);
        }

        for (size_t i = 0; i < indices.size() / 3; ++i) {
            auto normal = GetNormal(
                vertices[indices[3 * i + 0]].Position,
                vertices[indices[3 * i + 1]].Position,
                vertices[indices[3 * i + 2]].Position
            );

            vertices[indices[3 * i + 0]].Normal += normal;
            vertices[indices[3 * i + 1]].Normal += normal;
            vertices[indices[3 * i + 2]].Normal += normal;
        }

        for (auto& vertex : vertices) {
            vertex.Normal = glm::normalize(vertex.Normal);
        }
    }


    std::pair<glm::vec3, glm::vec3> MinMaxVector(glm::vec3* vertices, size_t size) {
        glm::vec3 maxVec{ -1.0f * std::numeric_limits<float>::max() };
        glm::vec3 minVec{ std::numeric_limits<float>::max() };
        for (size_t i = 0; i < size; ++i) {
            minVec = glm::min(minVec, vertices[i]);
            maxVec = glm::max(maxVec, vertices[i]);
        }

        return { minVec, maxVec };
    }
}
