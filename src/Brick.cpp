#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, int points, int hp, const std::string& type)
    : x(x), y(y), width(width), height(height), points(points), hp(hp), type(type) {
}

bool Brick::hit() {
    hp--;
    return hp <= 0;
}

bool Brick::isDestroyed() const { return hp <= 0; }
float Brick::getX() const { return x; }
float Brick::getY() const { return y; }
float Brick::getWidth() const { return width; }
float Brick::getHeight() const { return height; }
int Brick::getPoints() const { return points; }
// const std::string& Brick::getType() const { return type; }

std::ostream& operator<<(std::ostream& os, const Brick& brick) {
    os << "Brick [x=" << brick.x << ", y=" << brick.y
       << ", width=" << brick.width << ", height=" << brick.height
       << ", points=" << brick.points << ", hp=" << brick.hp
       << ", type=" << brick.type << "]";
    return os;
}