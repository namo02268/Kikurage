#pragma once

#include "OpenGL/Shader.h"
#include "OpenGL/Texture2D.h"

namespace Kikurage {
	class IBL {
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

		void Init();
		void Update(float dt);
		void Draw();
	};
}

