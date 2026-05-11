#include "Paddle.h"

Paddle::Paddle(float x, float y, float height, float width, float speed)
    : x(x), y(y), height(height), width(width), speed(speed) {
}

void Paddle::moveLeft(float screenLeft) {
    if (x - speed >= screenLeft) {
        x -= speed;
    }
}

void Paddle::moveRight(float screenRight) {
    if (x + speed + width <= screenRight) {
        x += speed;
    }
}

float Paddle::getX() const { return x; }
float Paddle::getY() const { return y; }
float Paddle::getHeight() const { return height; }
float Paddle::getWidth() const { return width; }

std::ostream& operator<<(std::ostream& os, const Paddle& paddle) {
    os << "Paddle [x=" << paddle.x << ", y=" << paddle.y
       << ", width=" << paddle.width << ", height=" << paddle.height
       << ", speed=" << paddle.speed << "]";
    return os;
}