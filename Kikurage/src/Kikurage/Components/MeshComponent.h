#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Kikurage/Resource/Mesh/Mesh.h"
#include "Kikurage/ECS/Component.h"


struct MeshComponent : public Component {
public:
	Mesh* mesh;

public:
	MeshComponent(Mesh* mesh) : mesh(mesh) {}
};
