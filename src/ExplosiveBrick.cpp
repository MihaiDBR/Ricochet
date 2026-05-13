#include "ExplosiveBrick.h"
#include <iostream>

ExplosiveBrick::ExplosiveBrick(float x, float y, float width, float height)
: Brick(x, y, width, height, 15, 1) {
}

bool ExplosiveBrick::hitOn() {
    std::cout << "Ai distrus mai multe brick-uri, ai lovit un Explosive Brick" << std::endl;
    return Brick::hitOn();
}

std::string ExplosiveBrick::getType() const {
    return "explosive";

}

Brick* ExplosiveBrick::clone() const {
    return new ExplosiveBrick(*this);
}

void ExplosiveBrick::afisare(std::ostream& os) const {
    os << "ExplosiveBrick a bubuit la [x= " << x << ", y=" << y
       << ", hp= " << hp << ", points= " << points << "]";
}
