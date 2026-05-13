#pragma once
#include "Brick.h"

class ExplosiveBrick : public Brick {

protected:
    void afisare(std::ostream& os) const override;
public:
    ExplosiveBrick(float x, float y, float width, float height);
    bool hitOn() override;
    std::string getType() const override;
    Brick* clone() const override;
};

