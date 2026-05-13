#include "Brick.h"

int Brick::TotBricks = 0;

Brick::Brick(float x, float y, float width, float height, int points, int hp)
    : x(x), y(y), width(width), height(height), points(points), hp(hp){
    TotBricks++;
}

bool Brick::hitOn() {
    hp--;
    return hp <= 0;
}

bool Brick::isDestroyed() const { return hp <= 0; }
float Brick::getX() const { return x; }
float Brick::getY() const { return y; }
float Brick::getWidth() const { return width; }
float Brick::getHeight() const { return height; }
int Brick::getPoints() const { return points; }
int Brick::getTotBricks() { return TotBricks; }

void Brick::afisare(std::ostream& os) const {
    os << "Brick are [type: " << getType() <<
        ", x: " << x << ", y: " << y <<
        ", hp: " << hp << ", points: " << points << "]";
}

std::ostream& operator<<(std::ostream& os, const Brick& brick) {
    brick.afisare(os);
    return os;
}

