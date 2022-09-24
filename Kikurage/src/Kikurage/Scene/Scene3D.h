#pragma once

#include "Kikurage/Core/Window.h"
#include "Kikurage/ECS/Scene.h"

class Scene3D {
public:
	Scene3D();
	~Scene3D();

	void Init();
	void Update(float dt);
	void Draw();

	Scene* GetScene() { return m_scene; }

private:
	Scene* m_scene;
};

