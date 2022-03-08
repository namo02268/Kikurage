#pragma once

#include "System.h"

class IBL : public System {
private:

public:
	IBL();
	~IBL();

	void init() override;
	void update(float dt) override;
	void draw() override;
};

