#pragma once
#include "Brick.h"

class HardBrick : public Brick {
public:
    HardBrick(float x, float y, float width, float height);
    bool hitOn() override;
    std::string getType() const override;
    Brick* clone() const override;
};

