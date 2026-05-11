#include "Game.h"
#include <cassert>
#include <iostream>

int main() {
    Game g1(680, 440, 3);
    g1.spawnWave();
    std::cout << g1 << std::endl;

    g1.update();
    g1.update();
    g1.update();
    std::cout << g1 << std::endl;

    g1.moveLeft();
    g1.moveRight();
    g1.moveRight();
    std::cout << g1 << std::endl;

    Game g2(g1);
    assert(g1 == g2);
    std::cout << "CC: Copiere corecta" << std::endl;

    Game g3(680, 440, 5);
    g3 = g1;
    assert(g1 == g3);
    std::cout << "Op=: Copiere corecta" << std::endl;

    return 0;
}