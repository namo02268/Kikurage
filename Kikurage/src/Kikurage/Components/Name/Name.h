#pragma once

#include "Kikurage/ECS/Component.h"
#include "Utils/String.h"

namespace Kikurage {
	struct Name : public Component {
	private:
		fixedString<63> name;

	public:
		Name(fixedString<63>& name) : name(name) {}
		Name(const char* name) : name(name) {}
		fixedString<63>& GetName() { return this->name; }
		void Rename(fixedString<63>& name) { this->name = name; }
		void Rename(const char* name) { this->name = name; }
	};
}