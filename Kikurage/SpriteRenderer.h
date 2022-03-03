#pragma once

#include "System.h"
#include "Shader.h"

#include <array>

#include "Vertex.h"

class SpriteRenderer : public System {
private:
	Shader m_shader;

public:
	SpriteRenderer(Shader shader);
	~SpriteRenderer();

	void init() override;
	void update(float dt) override;
	void draw() override;
};