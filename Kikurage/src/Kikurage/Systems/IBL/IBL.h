#pragma once

#include "Kikurage/ECS/System.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"

namespace Kikurage {
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
		Texture2D brdfLUTTexture;

	public:
		IBL(Shader* pbrShader, Shader* backgroundShader);
		~IBL();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}

