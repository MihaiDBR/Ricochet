#pragma once
#include <iostream>
#include <string>

class Brick {
private:
    float x, y, width, height;
    int points, hp;
    std::string type;

public:
    Brick(float x, float y, float width, float height, int points, int hp, const std::string& type);
    bool hit();
    [[nodiscard]] bool isDestroyed() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    [[nodiscard]] int getPoints() const;
    [[nodiscard]] const std::string& getType() const;
    friend std::ostream& operator<<(std::ostream& os, const Brick& brick);
};