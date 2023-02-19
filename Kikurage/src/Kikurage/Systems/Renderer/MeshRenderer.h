#pragma once

#include "OpenGL/Shader.h"
#include "Nameko/ECS.h"

namespace Kikurage {
	class MeshRenderer : public Nameko::System {
	private:
		Shader* m_shader;

	public:
		MeshRenderer(Shader* shader);
		~MeshRenderer();

		void Init() override;
		void Update(float dt) override;
		void Draw() override;
	};
}
