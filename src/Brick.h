#pragma once
#include <iostream>
#include <string>

class Brick {
protected:
    float x, y, width, height;
    int points, hp;
    virtual void afisare(std::ostream& os) const;
    static int TotBricks;

public:
    Brick(float x, float y, float width, float height, int points, int hp);
    virtual ~Brick() = default;
    virtual bool hitOn();
    virtual std::string getType() const = 0;
    virtual Brick* clone() const =0;
    static int getTotBricks();

    [[nodiscard]] bool isDestroyed() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    [[nodiscard]] int getPoints() const;
    friend std::ostream& operator<<(std::ostream& os, const Brick& brick);
};