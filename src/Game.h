#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>
#include <memory>
#include <iostream>

class Game {
private:
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<std::unique_ptr<Brick>> bricks;
    int score;
    int lives;
    int wave;
    float screenWidth, screenHeight;

public:
    Game(float screenWidth, float screenHeight, int lives);
    Game(const Game& other);
    Game& operator=(const Game& other);
    ~Game();
    bool operator==(const Game& other) const;
    void spawnWave();
    void checkCollisions();
    void moveLeft();
    void moveRight();
    void update();
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    const std::vector<std::unique_ptr<Brick>>& getBricks() const;
};