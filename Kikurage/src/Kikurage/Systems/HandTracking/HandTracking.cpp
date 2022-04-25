#include "HandTracking.h"

#include "Kikurage/ECS/Scene.h"
#include "Kikurage/Components/TransformComponent.h"
#include "Kikurage/Components/IOControllerComponent.h"

HandTracking::HandTracking() {
	auto family = getComponentTypeID<TransformComponent>();
	m_requiredComponent[family] = true;
	family = getComponentTypeID<IOControllerComponent>();
	m_requiredComponent[family] = true;
}

HandTracking::~HandTracking() {

}

void HandTracking::init() {

}

void HandTracking::update(float dt) {
	for (auto& e : m_entityArray) {
		auto transfromComponent = m_parentScene->getComponent<TransformComponent>(e);
		auto controllerComponent = m_parentScene->getComponent<IOControllerComponent>(e);

		const Leap::Frame frame = controller.frame();
		Leap::HandList hands = frame.hands();
		for (Leap::HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
			// Get fingers
			const Leap::Hand hand = *hl;
			const Leap::FingerList fingers = hand.fingers();
			auto target = fingers[controllerComponent->fingerType].bone(static_cast<Leap::Bone::Type>(3)).nextJoint();

			if (target.x != 0.0f) {
				indexFinger = glm::vec3(target.x / 20, target.y / 20, target.z / 20);
				transfromComponent->position = indexFinger - glm::vec3(0.0f, 5.0f, 0.0f);
			}
		}

	}
}

void HandTracking::draw() {

}