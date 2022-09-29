#pragma once

#include "Kikurage/ECS/System.h"
#include "OpenGL//Shader.h"

class MeshRenderer : public System {
private:
	Shader* m_shader;

public:
	MeshRenderer(Shader* shader);
	~MeshRenderer();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
};

