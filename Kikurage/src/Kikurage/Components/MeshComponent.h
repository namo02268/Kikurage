#pragma once

#include "Kikurage/Resource/Model/Model.h"
#include "Kikurage/ECS/Component.h"

namespace Kikurage {
	struct ModelComponent : public Component {
	public:
		Model* model;

	public:
		ModelComponent(Model* model) : model(model) {}
	};
}
