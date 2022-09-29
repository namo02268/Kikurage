#pragma once
#include <bitset>

constexpr unsigned int MAX_COMPONENTS_FAMILY = 32;
constexpr unsigned int MAX_ENTITIES = 5000;
constexpr std::int32_t MAX_COMPONENTS = 5000;

using ComponentInstance = unsigned int;
using EntityID = unsigned int;
using ComponentTypeID = unsigned int;
using ComponentFamily = std::bitset<MAX_COMPONENTS_FAMILY>;