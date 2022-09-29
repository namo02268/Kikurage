#pragma once

#include "Kikurage/Core/Window.h"
#include "Kikurage/ECS/ECS.h"

class Scene3D {
public:
	Scene3D();
	~Scene3D();

	void Init();
	void Update(float dt);
	void Draw();

	ECS* GetScene() { return m_scene; }

private:
	ECS* m_scene;
};

