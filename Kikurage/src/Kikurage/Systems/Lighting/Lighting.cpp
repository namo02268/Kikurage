#include "Kikurage/Systems/Lighting/Lighting.h"

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/Components/Transform/Transform.h"
#include "Kikurage/Components/Light/Light.h"

namespace Kikurage {
	Lighting::Lighting() {}

	Lighting::~Lighting() {}

	void Lighting::Init() {}

	void Lighting::Update(float dt) {}

	void Lighting::Draw() {
		auto renderer = Application::GetInstance().GetRenderer();
		size_t num = 0;
		m_ecs->EachComponent<Transform, Light>([&](Transform& transform, Light& light) {
			renderer->ApplyLight(light, transform, num);
			num++;
		});
	}
}