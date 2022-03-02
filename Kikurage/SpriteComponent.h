#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>

#include "Component.h"
#include "Texture2D.h"
#include "Vertex.h"

enum SpriteMode {
	single,
	multiple
};

class SpriteComponent : public Component {
public:
	Texture2D texture;
	glm::vec3 color = glm::vec3(1.0f);
	int mode = single;
//	float PixelsPerUnit = 100;

public:
	SpriteComponent() {}
	SpriteComponent(Texture2D texture, glm::vec3 color) : texture(texture), color(color) {}
};
