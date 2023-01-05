#pragma once

#include "Kikurage/ECS/Component.h"

namespace Kikurage {
	constexpr int MAX_NAME_SIZE = 256;

	struct Name : public Component {
	private:
		char name[MAX_NAME_SIZE];

	public:
		Name(const char* name) { strcpy_s(this->name, MAX_NAME_SIZE, name); }
		char* GetName() { return this->name; }
		void Rename(const char* name) { strcpy_s(this->name, MAX_NAME_SIZE, name); }
	};
}