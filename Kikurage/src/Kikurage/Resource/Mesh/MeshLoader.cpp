#include "Kikurage/Resource/Mesh/MeshLoader.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void processNode(aiNode* node, const aiScene* scene, MeshInfo& mesh);
void processMesh(aiMesh* aimesh, const aiScene* scene, MeshInfo& mesh);
std::pair<glm::vec3, glm::vec3> MinMaxVector(glm::vec3* vertices, size_t size);

MeshInfo MeshLoader::LoadFromFile(const char* path) {
    ObjectInfo object;
    MeshInfo mesh;

    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return mesh;
    }

    object.meshes.reserve((size_t)scene->mNumMeshes);

    std::cout << "Meshes : " << scene->mNumMeshes << std::endl;
    std::cout << "materials : " << scene->mNumMaterials << std::endl;


    /*
    glm::vec3 minVec{};
    glm::vec3 maxVec{};

    for (size_t i = 0; i < scene->mNumMeshes; ++i) {
        auto& mesh = scene->mMeshes[i];
        auto coords = MinMaxVector((glm::vec3*)mesh->mVertices, (size_t)mesh->mNumVertices);

        minVec = coords.first;
        maxVec = coords.second;
    }

    std::cout << minVec.x << std::endl;
    std::cout << maxVec.x << std::endl;
    */

    for (size_t i = 0; i < (size_t)scene->mNumMeshes; ++i) {
        auto& mesh = scene->mMeshes[i];
        std::cout << mesh->mName.C_Str() << std::endl;
    }
    // process ASSIMP's root node recursively(Ä‹A“I)
//    processNode(scene->mRootNode, scene, mesh);

    return mesh;
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


void processNode(aiNode* node, const aiScene* scene, MeshInfo& mesh) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(aimesh, scene, mesh);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, mesh);
    }
}

void processMesh(aiMesh* aimesh, const aiScene* scene, MeshInfo& mesh) {
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

        mesh.vertices.push_back(vertex);
    }

    // walk through each of the mesh's face
    for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
        aiFace face = aimesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            mesh.indices.push_back(face.mIndices[j]);
    }
}
