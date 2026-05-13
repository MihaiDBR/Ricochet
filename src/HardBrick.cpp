#include "HardBrick.h"
#include <iostream>

HardBrick::HardBrick(float x, float y, float width, float height)
: Brick(x, y, width, height, 20, 2) {
}

bool HardBrick::hitOn() {
    std::cout << "Ai lovit un Brick hard, daca nu s-a distrus, mai trebuie lovit o data" << std::endl;
    return Brick::hitOn();
}

std::string HardBrick::getType() const {
    return "hard";
}

Brick* HardBrick::clone() const {
    return new HardBrick(*this);
}
