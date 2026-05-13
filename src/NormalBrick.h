#pragma once
#include "Brick.h"

class NormalBrick : public Brick {
    public:
    NormalBrick(float x, float y, float width, float height);
    bool hitOn() override;
    std::string getType() const override;
    Brick* clone() const override;
};

