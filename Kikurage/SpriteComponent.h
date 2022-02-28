#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include "Texture2D.h"

class SpriteComponent : public Component {
public:
	Texture2D texture;
	float PixelsPerUnit = 100;
	glm::vec3 color;

public:
	SpriteComponent(Texture2D texture) : texture(texture) {}
};
