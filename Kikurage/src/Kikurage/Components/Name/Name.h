#pragma once

#include "Kikurage/ECS/Component.h"
#include "Utils/String.h"

namespace Kikurage {
	struct Name : public Component {
	private:
		fixedString<31> name;

	public:
		Name(fixedString<31>& name) : name(name) {}
		Name(const char* name) : name(name) {}
		fixedString<31>& GetName() { return this->name; }
		void Rename(fixedString<31>& name) { this->name = name; }
	};
}