#pragma once
#include "Kikurage/Systems/Renderer/CameraController.h"

class RenderController {
private:
	CameraController* cameraController;

public:
	RenderController() {}
	~RenderController() {}

public:
	void RenderStart() {}
	void Flush() {}
	void RenderEnd() {}
};