#pragma once

#include "System.h"
#include "Shader.h"

class Renderer : public System {
private:
	Shader m_shader;

public:
	Renderer(Shader shader);
	~Renderer();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

