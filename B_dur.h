#pragma once

#include "Brick.h"

class B_dur : public Brick
{
public:

	B_dur();

	B_dur(float x, float y);

	void hit() override;

};

