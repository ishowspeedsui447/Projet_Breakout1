#pragma once

#include "Brick.h"

class B_incassable : public Brick
{

public:
    B_incassable();

    B_incassable(float x, float y);

    void hit() override;

    bool isDestroyed() const override;
};

