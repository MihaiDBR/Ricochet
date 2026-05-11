#include "Ball.h"

Ball::Ball(float x, float y, float dx, float dy, float radius)
    : x(x), y(y), dx(dx), dy(dy),
    radius(radius) {
}

void Ball::move() {
    x += dx;
    y += dy;
}

void Ball::bounceX() { 
    dx = -dx; 
}
void Ball::bounceY() { 
    dy = -dy; 
}

void Ball::reset(float newX, float newY) {
    x = newX;
    y = newY;
    dx = 3;
    dy = -3;
}

float Ball::getX() const { return x; }
float Ball::getY() const { return y; }
float Ball::getRadius() const { return radius; }
float Ball::getDy() const { return dy; }

std::ostream& operator<<(std::ostream& os, const Ball& ball) {
    os << "Ball [x=" << ball.x
       << ", y=" << ball.y
       << ", dx=" << ball.dx
       << ", dy=" << ball.dy
       << ", radius=" << ball.radius
       << "]";
    return os;
}