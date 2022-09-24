#include "Kikurage/Systems/Camera/CameraSystem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Kikurage/Core/Application/Application.h"
#include "Kikurage/ECS/Scene.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/cameraComponent.h"

CameraSystem::CameraSystem() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<CameraComponent>();
	m_requiredComponent[family] = true;
}

CameraSystem::~CameraSystem() {

}

void CameraSystem::addShader(Shader* shader) {
	m_shaders.push_back(shader);
}

void CameraSystem::init() {

}

void CameraSystem::update(float dt) {
	for (auto& e : m_entityArray) {
		auto trans = m_parentScene->getComponent<TransformComponent>(e);
		camera.UpdateProjectionMatrix();
		camera.HandleKeyboard(*trans, dt);
		camera.HandleMouse(*trans, dt);
	}
}

void CameraSystem::draw() {	
	for (auto& e : m_entityArray) {
		auto trans = m_parentScene->getComponent<TransformComponent>(e);

		for (auto& shader : m_shaders) {
			auto view = glm::inverse(trans->worldMatrix);
			auto renderer = Application::GetInstance().GetRenderer();

			camera.SetAspectRatio(static_cast<float>(renderer->GetWidth()) / static_cast<float>(renderer->GetHeight()));

			shader->Bind();
			shader->SetUniform("cameraPos", trans->position);
			shader->SetUniform("projection", camera.GetProjectionMatrix());
			shader->SetUniform("view", view);
		}
	}
}