#pragma once
#include <iostream>

class Paddle {
private:
    float x, y, height, width, speed;

public:
    Paddle(float x, float y, float height, float width, float speed);
    void moveLeft(float screenLeft);
    void moveRight(float screenRight);
    float getX() const;
    float getY() const;
    float getHeight() const;
    float getWidth() const;
    friend std::ostream& operator<<(std::ostream& os, const Paddle& paddle);
};