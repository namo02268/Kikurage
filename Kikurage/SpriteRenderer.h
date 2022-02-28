#pragma once

#include "System.h"
#include "Shader.h"

class SpriteRenderer : public System {
private:
	Shader m_shader;
	unsigned int m_quadVAO;

public:
	SpriteRenderer(Shader shader);
	~SpriteRenderer();

	void init() override;
	void update() override;
	void draw() override;
};