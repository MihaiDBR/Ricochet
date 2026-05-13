#include "NormalBrick.h"
#include <iostream>

NormalBrick::NormalBrick(float x, float y, float width, float height)
: Brick(x, y, width, height, 10, 1) {
}

bool NormalBrick::hitOn() {
    std::cout << "Ai lovit un Brick normal" << std::endl;
    return Brick::hitOn();
}

std::string NormalBrick::getType() const {
    return "normal";
}

Brick* NormalBrick::clone() const {
    return new NormalBrick(*this);
}
