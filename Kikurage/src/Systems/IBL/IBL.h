#pragma once

#include "ECS/System.h"
#include "Resources/Shader/Shader.h"

class IBL : public System {
private:
	Shader* pbrShader;
	Shader* equirectangularToCubemapShader;
	Shader* irradianceShader;
	Shader* prefilterShader;
	Shader* brdfShader;
	Shader* backgroundShader;

	unsigned int envCubemap;
	unsigned int irradianceMap;
	unsigned int prefilterMap;
	unsigned int brdfLUTTexture;

public:
	IBL(Shader* pbrShader, Shader* backgroundShader);
	~IBL();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

