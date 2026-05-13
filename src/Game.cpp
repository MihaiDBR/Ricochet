#include "Game.h"
#include "NormalBrick.h"
#include "HardBrick.h"
#include "ExplosiveBrick.h"
#include "GameException.h"
#include "InvisibleBrick.h"
#include <algorithm>



Game::Game(float screenWidth, float screenHeight, int lives)
    : paddle(screenWidth / 2 - 60, screenHeight - 30, 12, 120, 7),
      score(0),
      lives(lives),
      wave(0),
      screenWidth(screenWidth),
      screenHeight(screenHeight)
{
    if (screenWidth < 0 || screenHeight < 0)
        throw ConfigGresit("Ecran prea mic");
    if (lives <= 0)
        throw ConfigGresit("Nu mai ai suficiente vieti sa continui");
    balls.push_back(Ball(screenWidth / 2, screenHeight - 50, 3, -3, 6));
}

Game::Game(const Game& other)
    : paddle(other.paddle),
      balls(other.balls),
      score(other.score),
      lives(other.lives),
      wave(other.wave),
      screenWidth(other.screenWidth),
      screenHeight(other.screenHeight)
{
    for (const auto& brick : other.bricks) {
        bricks.push_back(std::unique_ptr<Brick>(brick->clone()));
    }
    std::cout << "Constructor de copiere al lui Game" << std::endl;
}

Game& Game::operator=(const Game& other) {
    if (this != &other) {
        Game temporar(other);
        std::swap(paddle, temporar.paddle);
        std::swap(balls, temporar.balls);
        std::swap(bricks, temporar.bricks);
        std::swap(score, temporar.score);
        std::swap(lives, temporar.lives);
        std::swap(wave, temporar.wave);
        std::swap(screenWidth, temporar.screenWidth);
        std::swap(screenHeight, temporar.screenHeight);
    }
    std::cout << "Operator = copiere pentru Game" << std::endl;
    return *this;
}

Game::~Game() {
    std::cout << "Destructor pentru Game" << std::endl;
}

bool Game::operator==(const Game& other) const {
    return score == other.score && lives == other.lives && wave == other.wave;
}

void Game::spawnWave() {
    wave++;
    bricks.clear();
    int rows = std::min(2 + wave, 6);
    int cols = std::min(5 + wave, 10);
    float brickWidth = 60;
    float brickHeight = 20;
    float gap = 10;
    float offsetX = (screenWidth - cols * (brickWidth + gap)) / 2;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            float x = offsetX + c * (brickWidth + gap);
            float y = 40 + r * (brickHeight + gap);
            if (wave > 1 && (r * cols + c) % 3 == 0) {
                bricks.push_back(std::make_unique<HardBrick>(x, y, brickWidth, brickHeight));
            } else if (wave > 2 && (r * cols + c) % 5 == 0) {
                bricks.push_back(std::make_unique<ExplosiveBrick>(x, y, brickWidth, brickHeight));
            } else if (wave > 3 && (r * cols + c) % 7 == 0) {
                bricks.push_back(std::make_unique<InvisibleBrick>(x, y, brickWidth, brickHeight));
            } else {
                bricks.push_back(std::make_unique<NormalBrick>(x, y, brickWidth, brickHeight));
            }
        }
    }
}

const std::vector<std::unique_ptr<Brick>>& Game::getBricks() const {
    return bricks;
}

void Game::checkCollisions() {
    for (auto& ball : balls) {
        if (ball.getX() - ball.getRadius() <= 0 || ball.getX() + ball.getRadius() >= screenWidth)
            ball.bounceX();

        if (ball.getY() - ball.getRadius() <= 0)
            ball.bounceY();

        if (ball.getY() > screenHeight) {
            lives--;
            ball.reset(screenWidth / 2, screenHeight - 50);
            continue;
        }

        if (ball.getDy() > 0 &&
            ball.getY() + ball.getRadius() >= paddle.getY() &&
            ball.getX() >= paddle.getX() &&
            ball.getX() <= paddle.getX() + paddle.getWidth())
            ball.bounceY();

        for (auto& brick : bricks) {
            if (ball.getX() + ball.getRadius() > brick->getX() &&
                ball.getX() - ball.getRadius() < brick->getX() + brick->getWidth() &&
                ball.getY() + ball.getRadius() > brick->getY() &&
                ball.getY() - ball.getRadius() < brick->getY() + brick->getHeight()) {
                ball.bounceY();
                if (brick->hitOn()) {
                    score += brick->getPoints();
                }
                break;
            }
        }
    }
    bricks.erase(
        std::remove_if(bricks.begin(), bricks.end(),
            [](const std::unique_ptr<Brick>& b) { return b->isDestroyed(); }),
        bricks.end());
}

void Game::moveLeft() { paddle.moveLeft(0); }
void Game::moveRight() { paddle.moveRight(screenWidth); }

void Game::update() {
    for (auto& ball : balls)
        ball.move();
    checkCollisions();
    if (bricks.empty())
        spawnWave();
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "____-Game-____" << std::endl;
    os << "Score: " << game.score << ", Lives: " << game.lives << ", Wave: " << game.wave << std::endl;
    os << game.paddle << std::endl;
    for (const auto& ball : game.balls) {
        os << ball << std::endl;
    }
    for (const auto& brick : game.bricks) {
        os << *brick << std::endl;
    }
    return os;
}