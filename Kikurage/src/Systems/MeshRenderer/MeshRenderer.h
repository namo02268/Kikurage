#pragma once

#include "ECS/System.h"
#include "Resources/Shader/Shader.h"

class MeshRenderer : public System {
private:
	Shader* m_shader;

public:
	MeshRenderer(Shader* shader);
	~MeshRenderer();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

