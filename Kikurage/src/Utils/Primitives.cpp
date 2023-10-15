#include "Utils/Primitives.h"
#include "Utils/Math.h"

namespace Kikurage {
	Mesh Primitives::CreateCube(size_t size) {
		MeshInfo meshInfo;

		// Vertices
		std::vector<Vertex> vertices = {
            // back face
            { Vector3(-1.0f, -1.0f, -1.0f), Vector3( 0.0f,  0.0f, -1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
            { Vector3( 1.0f,  1.0f, -1.0f), Vector3( 0.0f,  0.0f, -1.0f), Vector2(1.0f, 1.0f) }, // top-right
            { Vector3( 1.0f, -1.0f, -1.0f), Vector3( 0.0f,  0.0f, -1.0f), Vector2(1.0f, 0.0f) }, // bottom-right         
            { Vector3( 1.0f,  1.0f, -1.0f), Vector3( 0.0f,  0.0f, -1.0f), Vector2(1.0f, 1.0f) }, // top-right
            { Vector3(-1.0f, -1.0f, -1.0f), Vector3( 0.0f,  0.0f, -1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
            { Vector3(-1.0f,  1.0f, -1.0f), Vector3( 0.0f,  0.0f, -1.0f), Vector2(0.0f, 1.0f) }, // top-left
            // front face
            { Vector3(-1.0f, -1.0f,  1.0f), Vector3( 0.0f,  0.0f,  1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
            { Vector3( 1.0f, -1.0f,  1.0f), Vector3( 0.0f,  0.0f,  1.0f), Vector2(1.0f, 0.0f) }, // bottom-right
            { Vector3( 1.0f,  1.0f,  1.0f), Vector3( 0.0f,  0.0f,  1.0f), Vector2(1.0f, 1.0f) }, // top-right
            { Vector3( 1.0f,  1.0f,  1.0f), Vector3( 0.0f,  0.0f,  1.0f), Vector2(1.0f, 1.0f) }, // top-right
            { Vector3(-1.0f,  1.0f,  1.0f), Vector3( 0.0f,  0.0f,  1.0f), Vector2(0.0f, 1.0f) }, // top-left
            { Vector3(-1.0f, -1.0f,  1.0f), Vector3( 0.0f,  0.0f,  1.0f), Vector2(0.0f, 0.0f) }, // bottom-left
            // left face
            { Vector3(-1.0f,  1.0f,  1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-right
            { Vector3(-1.0f,  1.0f, -1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-left
            { Vector3(-1.0f, -1.0f, -1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-left
            { Vector3(-1.0f, -1.0f, -1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-left
            { Vector3(-1.0f, -1.0f,  1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(0.0f, 0.0f) }, // bottom-right
            { Vector3(-1.0f,  1.0f,  1.0f), Vector3(-1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-right
            // right face
            { Vector3( 1.0f,  1.0f,  1.0f), Vector3( 1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-left
            { Vector3( 1.0f, -1.0f, -1.0f), Vector3( 1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-right
            { Vector3( 1.0f,  1.0f, -1.0f), Vector3( 1.0f,  0.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-right         
            { Vector3( 1.0f, -1.0f, -1.0f), Vector3( 1.0f,  0.0f,  0.0f), Vector2(0.0f, 1.0f) }, // bottom-right
            { Vector3( 1.0f,  1.0f,  1.0f), Vector3( 1.0f,  0.0f,  0.0f), Vector2(1.0f, 0.0f) }, // top-left
            { Vector3( 1.0f, -1.0f,  1.0f), Vector3( 1.0f,  0.0f,  0.0f), Vector2(0.0f, 0.0f) }, // bottom-left     
             // bottom face
            { Vector3(-1.0f, -1.0f, -1.0f), Vector3( 0.0f, -1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-right
            { Vector3( 1.0f, -1.0f, -1.0f), Vector3( 0.0f, -1.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-left
            { Vector3( 1.0f, -1.0f,  1.0f), Vector3( 0.0f, -1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-left
            { Vector3( 1.0f, -1.0f,  1.0f), Vector3( 0.0f, -1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-left
            { Vector3(-1.0f, -1.0f,  1.0f), Vector3( 0.0f, -1.0f,  0.0f), Vector2(0.0f, 0.0f) }, // bottom-right
            { Vector3(-1.0f, -1.0f, -1.0f), Vector3( 0.0f, -1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-right
             // top face
            { Vector3(-1.0f,  1.0f, -1.0f), Vector3( 0.0f,  1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-left
            { Vector3( 1.0f,  1.0f , 1.0f), Vector3( 0.0f,  1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-right
            { Vector3( 1.0f,  1.0f, -1.0f), Vector3( 0.0f,  1.0f,  0.0f), Vector2(1.0f, 1.0f) }, // top-right     
            { Vector3( 1.0f,  1.0f,  1.0f), Vector3( 0.0f,  1.0f,  0.0f), Vector2(1.0f, 0.0f) }, // bottom-right
            { Vector3(-1.0f,  1.0f, -1.0f), Vector3( 0.0f,  1.0f,  0.0f), Vector2(0.0f, 1.0f) }, // top-left
            { Vector3(-1.0f,  1.0f,  1.0f), Vector3( 0.0f,  1.0f,  0.0f), Vector2(0.0f, 0.0f) }  // bottom-left
        };

		meshInfo.vertices = vertices;

		// Mesh
		Mesh mesh;
		mesh.CreateBuffers(meshInfo);

		return mesh;
	}
}
