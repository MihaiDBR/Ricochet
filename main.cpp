#include <iostream>
#include <array>
#include <vector>
#include <cmath>

class Paddle {

private:
    float x, y, height, width, speed;

public:
    Paddle(float x, float y, float height, float width, float speed)
        : x(x),
          y(y),
          height(height),
          width(width),
          speed(speed) {
    }

    void moveLeft(float screenLeft) {
        if (x - speed >= screenLeft) {
            x -= speed;
        }
    }

    void moveRight(float screenRight) {
        if (x + speed + width <= screenRight) {
            x += speed;
        }
    }

    float getX() const { return x;}
    float getY() const { return y;}
    float getHeight() const { return height;}
    float getWidth() const { return width;}

    friend std::ostream& operator<<(std::ostream& os, const Paddle& paddle) {
        os << "Paddle " << "[" << "x=" << paddle.x << ", y=" << paddle.y << ", width=" << paddle.width <<
            ", height=" << paddle.height << ", speed=" << paddle.speed << "]";
        return os;
    };
};

class Ball {

private:
    float x, y, dx, dy, radius;

public:

    Ball(float x, float y, float dx, float dy, float radius)
        : x(x),
          y(y),
          dx(dx),
          dy(dy),
          radius(radius) {
    }

    void move() {
        x += dx;
        y += dy;
    }

    void bounceX() {
        dx = -dx;
    }

    void bounceY() {
        dy = -dy;
    }

    float getX() const { return x;}
    float getY() const { return y;}
    float getRadius() const { return radius;}
    float getDy() const { return dy;}

    friend std::ostream& operator<<(std::ostream& os, const Ball& ball) {
        os << "Ball " << "[" << "x=" << ball.x << ", y=" << ball.y << ", dx=" << ball.dx <<
            ", dy=" << ball.dy << ", radius=" << ball.radius << "]";
        return os;
    }

};

int main() {

    return 0;
}
