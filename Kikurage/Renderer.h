#pragma once

#include "System.h"
#include "Shader.h"

class Renderer : public System {
private:
	Shader* m_shader;
	glm::quat oldQuat = glm::quat(glm::vec3(0.0f));
	glm::vec3 oldRadians = glm::vec3(0.0f);

public:
	Renderer(Shader* shader);
	~Renderer();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

