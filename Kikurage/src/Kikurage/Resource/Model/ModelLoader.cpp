#include "Kikurage/Resource/Model/ModelLoader.h"
#include "Kikurage/Core/Application/Application.h"

#include "Kikurage/Components/Name/Name.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Mesh/Mesh.h"
#include "Kikurage/Components/MaterialComponent.h"
#include "Utils/Math.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Kikurage {
    void ModelLoader::LoadEntity(const char* path, float size) {
        auto model = LoadFromFile(path);
        auto ecs = Application::GetInstance().GetECS();

        auto root = ecs->CreateEntity();
        ecs->AddComponent(root, Transform(Vector3(0.0f), Vector3(size), Vector3(0.0f)));
        ecs->GetComponent<Name>(root)->Rename(path);

        for (auto& mesh : model.meshes) {
            auto entity = ecs->CreateEntity();
            ecs->AddComponent(entity, Transform(mesh.position, Vector3(1.0f), Vector3(0.0f)));
            ecs->AddComponent(entity, Mesh(mesh));
            ecs->AddComponent<MaterialComponent>(entity, MaterialComponent());
            ecs->GetComponent<Name>(entity)->Rename(mesh.name);
            ecs->AddRelationship(root, entity);
        }
    }

    ModelInfo ModelLoader::LoadFromFile(const char* path) {
        std::cout << "Loading " << path << "..." << std::endl;

        ModelInfo object;

        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return object;
        }

        // -----------------------Load Mesh----------------------- //
        object.meshes.resize((size_t)scene->mNumMeshes);
        for (size_t i = 0; i < (size_t)scene->mNumMeshes; ++i) {
            auto& mesh = scene->mMeshes[i];
            auto& meshInfo = object.meshes[i];

            meshInfo.name = mesh->mName.C_Str();
            meshInfo.hasNormals = mesh->HasNormals();
            meshInfo.hasTextureCoords = mesh->HasTextureCoords(0);

            // Center
            Vector3 Min{ std::numeric_limits<float>::max() };
            Vector3 Max{ std::numeric_limits<float>::min() };

            for (size_t i = 0; i < (size_t)mesh->mNumVertices; ++i) {
                Min.x = std::min(mesh->mVertices[i].x, Min.x);
                Max.x = std::max(mesh->mVertices[i].x, Max.x);
                Min.y = std::min(mesh->mVertices[i].y, Min.y);
                Max.y = std::max(mesh->mVertices[i].y, Max.y);
                Min.z = std::min(mesh->mVertices[i].z, Min.z);
                Max.z = std::max(mesh->mVertices[i].z, Max.z);
            }

            auto center = (Min + Max) * 0.5f;
            Min -= center;
            Max -= center;
            meshInfo.position = center;

            // vertices
            meshInfo.vertices.resize((size_t)mesh->mNumVertices);
            for (size_t i = 0; i < (size_t)mesh->mNumVertices; ++i) {
                meshInfo.vertices[i].Position = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z) - center;
                meshInfo.vertices[i].Normal = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

                if (meshInfo.hasTextureCoords) {
                    meshInfo.vertices[i].TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
                }
            }

            // aabb
            meshInfo.aabb = { Min, Max };

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

        // -----------------------Load Material----------------------- //
        object.materials.resize((size_t)scene->mNumMaterials);
        for (size_t i = 0; i < object.materials.size(); ++i) {
            auto& material = scene->mMaterials[i];
            auto& materialInfo = object.materials[i];

            materialInfo.name = material->GetName().C_Str();

            std::cout << "Material Count" << material->GetTextureCount(aiTextureType_DIFFUSE) << std::endl;
        }

        return object;
    }

    void ModelLoader::GenerateNormals(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        for (auto& vertex : vertices) {
            vertex.Normal = Vector3(0.0f);
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
            vertex.Normal = Normalize(vertex.Normal);
        }
    }
}
