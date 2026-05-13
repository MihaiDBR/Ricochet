#pragma once
#include "Brick.h"

class InvisibleBrick : public Brick {
protected:
    void afisare(std::ostream& os) const override;
public:
    InvisibleBrick(float x, float y, float width, float height);
    bool hitOn() override;
    std::string getType() const override;
    Brick* clone() const override;
}