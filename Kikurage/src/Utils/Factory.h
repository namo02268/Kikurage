#pragma once

template<typename T>
struct Resource {
	T value;
	int id = 0;
};

template<typename T>
class Factory {
public:
	Factory() = default;
	~Factory() = default;

	void Create() {}
	void Destroy() {}
};