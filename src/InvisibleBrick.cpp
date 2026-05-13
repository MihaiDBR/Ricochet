#include "InvisibleBrick.h"
#include <iostream>

InvisibleBrick::InvisibleBrick(float x, float y, float width, float height)
    : Brick(x, y, width, height, 25, 1) {}

bool InvisibleBrick::hitOn() {
    std::cout << "Ai lovit un Brick invizibil" << std::endl;
    return Brick::hitOn();
}

std::string InvisibleBrick::getType() const {
    return "invisible";
}

Brick* InvisibleBrick::clone() const {
    return new InvisibleBrick(*this);
}

void InvisibleBrick::afisare(std::ostream& os) const {
    os << "InvisibleBrick [" << "x: " << x << ",y: " << y
    << ",hp: " << hp << ",points: " << points << "]";
}
