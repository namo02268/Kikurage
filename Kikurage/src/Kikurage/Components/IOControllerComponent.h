#pragma once

#include "Kikurage/ECS/Component.h"

enum class Finger {
	Thumb,
	Index,
	Middle,
	Ring,
	Pinky
};

enum class Bone {
	Metacarpal,
	Proximal,
	Middle,
	Distal
};

class IOControllerComponent : public Component {
public:
	Finger fingerType = Finger::Index;
	Bone boneType = Bone::Distal;

public:
	IOControllerComponent() {}
	IOControllerComponent(Finger fingerType, Bone boneType) : fingerType(fingerType), boneType(boneType) {}
};