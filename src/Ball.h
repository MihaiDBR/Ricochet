#pragma once
#include <iostream>

class Ball {
private:
    float x, y, dx, dy, radius;

public:
    Ball(float x, float y, float dx, float dy, float radius);

    void move();
    void bounceX();
    void bounceY();
    void reset(float newX, float newY);

    bool operator==(const Ball& other) const;

    float getX() const;
    float getY() const;
    float getRadius() const;
    float getDy() const;

    friend std::ostream& operator<<(std::ostream& os, const Ball& ball);
};