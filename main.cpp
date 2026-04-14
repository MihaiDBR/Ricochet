#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

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

    void reset(float newX, float newY) {
        x = newX;
        y = newY;
        dx = 3;
        dy = -3;
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

class Brick {
private:
    float x, y, width, height;
    int points, hp;
    std::string type;

public:
    Brick(float x, float y, float width, float height, int points, int hp, const std::string& type)
        : x(x),
          y(y),
          width(width),
          height(height),
          points(points),
          hp(hp),
          type(type) {
    }

    bool hit() {
        hp--;
        return hp <= 0;
    }

    bool isDestroyed() const {
        return hp <= 0;
    }

    float getX() const { return x;}
    float getY() const { return y;}
    float getWidth() const { return width;}
    float getHeight() const { return height;}
    int getPoints() const { return points;}

    // de adaugat iar GetType


    friend std::ostream& operator<<(std::ostream& os, const Brick& brick) {
        os << "Brick " << "[" << "x=" << brick.x << ", y=" << brick.y << ", width=" << brick.width <<
            ", height=" << brick.height << ", points=" << brick.points << ", hp=" << brick.hp <<
            ", type=" << brick.type << "]";
        return os;
    }
};

class Game {
private:
    Paddle paddle;
    std::vector<Ball> balls; // Acesta o sa fie de folos la M2, pentru superputeri :) (sa nu uit eu)
    std::vector<Brick> bricks;
    int score;
    int lives;
    int wave;
    float screenWidth, screenHeight;

public:
    Game(float screenWidth, float screenHeight, int lives)
        : paddle(screenWidth / 2 - 60, screenHeight - 30, 12, 120, 7),
          score(0),
          lives(lives),
          wave(0),
          screenWidth(screenWidth),
          screenHeight(screenHeight)
    {
        balls.push_back(Ball(screenWidth / 2, screenHeight - 50, 3, -3, 6));
    }

    Game(const Game& other)
        : paddle(other.paddle),
          balls(other.balls),
          bricks(other.bricks),
          score(other.score),
          lives(other.lives),
          wave(other.wave),
          screenWidth(other.screenWidth),
          screenHeight(other.screenHeight)
    {
        std::cout << "Constructor de copiere al lui Game" << std::endl;
    }

    Game& operator=(const Game& other) {
        paddle = other.paddle;
        balls = other.balls;
        bricks = other.bricks;
        score = other.score;
        lives = other.lives;
        wave = other.wave;
        screenWidth = other.screenWidth;
        screenHeight = other.screenHeight;
        std::cout << "Operator = copiere pentru Game" << std::endl;
        return *this;
    }

    ~Game() {
        std::cout << "Destructor pentru Game" << std::endl;
    }

    bool operator==(const Game& other) const {
        return score == other.score && lives == other.lives && wave == other.wave;
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << "____-Game-____" << std::endl;
        os << "Score: " << game.score << ", Lives: " << game.lives << ", Wave: " << game.wave << std::endl;
        os << game.paddle << std::endl;
        for (const auto& ball : game.balls) {
            os << ball << std::endl;
        }
        for (const auto& brick : game.bricks) {
            os << brick << std::endl;
        }
        return os;
    }

    // INCEREMENTARE "NIVELE"
    void spawnWave() {
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
                    bricks.push_back(Brick(x, y, brickWidth, brickHeight, 20, 2, "hard"));
                } else {
                    bricks.push_back(Brick(x, y, brickWidth, brickHeight, 10, 1, "normal"));
                }
            }
        }
    }

    void checkCollisions() {
        for (auto& ball: balls) {
            // Walls
            if (ball.getX() - ball.getRadius() <= 0 || ball.getX() + ball.getRadius() >= screenWidth)
                ball.bounceX();

            // Up
            if (ball.getY() - ball.getRadius() <= 0)
                ball.bounceY();

            // Down
            if (ball.getY() > screenHeight) {
                lives--;
                ball.reset(screenWidth / 2, screenHeight - 50);
                continue;
            }
            // Paddle
            if (ball.getDy() > 0 &&
                ball.getY() + ball.getRadius() >= paddle.getY() &&
                ball.getX() >= paddle.getX() &&
                ball.getX() <= paddle.getX() + paddle.getWidth())
                    ball.bounceY();

            // Bricks
            for (auto& brick: bricks) {
                if (ball.getX() + ball.getRadius() > brick.getX() &&
                    ball.getX() - ball.getRadius() < brick.getX() + brick.getWidth() &&
                    ball.getY() + ball.getRadius() > brick.getY() &&
                    ball.getY() - ball.getRadius() < brick.getY() + brick.getHeight()) {
                    ball.bounceY();
                    if (brick.hit()) {
                        score += brick.getPoints();
                    }
                    break;
                    }
                }
            }
        bricks.erase(
        std::remove_if(bricks.begin(), bricks.end(),
            [](const Brick& b) { return b.isDestroyed(); }),bricks.end());
    }

    void moveLeft() { paddle.moveLeft(0); }
    void moveRight() { paddle.moveRight(screenWidth); }

    void update() {
        for (auto& ball: balls)
            ball.move();
        checkCollisions();
        if (bricks.empty())
            spawnWave();
    }

};

int main() {
    // Creez jocul
    Game g1(680, 440, 3);
    g1.spawnWave();
    std::cout << g1 << std::endl;

    // Cateva tick-uri de joc
    g1.update();
    g1.update();
    g1.update();
    std::cout << g1 << std::endl;

    // Test constructor de copiere
    Game g2(g1);
    assert(g1 == g2);
    std::cout << "CC: Copiere corecta" << std::endl;

    // Miscarea paddle-ului
    g1.moveLeft();
    g1.moveRight();
    g1.moveRight();
    std::cout << g1 << std::endl;

    // Test operator=
    Game g3(680, 440, 5);
    g3 = g1;
    assert(g1 == g3);
    std::cout << "Op=: Copiere corecta" << std::endl;

    // Destructorii se apeleaza automat la final

    return 0;
}
