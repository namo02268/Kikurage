#pragma once

namespace Kikurage {
	class Scene3D {
	public:
		Scene3D();
		~Scene3D();

		void Init();
		void Update(float dt);
		void Draw();
	};
}
