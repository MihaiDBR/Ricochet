#include "Game.h"
#include "HardBrick.h"
#include "ExplosiveBrick.h"
#include "GameException.h"
#include <cassert>
#include <iostream>



int main() {
    try {
        Game g1(680, 440, 3);
        g1.spawnWave();
        g1.spawnWave();
        g1.spawnWave();
        std::cout << g1 << std::endl;

        //Ver Dynamic_cast ca fct
        for (const auto& brick : g1.getBricks()) {
            if (auto* hard = dynamic_cast<const HardBrick*> (brick.get())) {
                std::cout << "Am gasit un HardBrick la x=" << hard->getX() << std::endl;
            } else if (auto* explosive = dynamic_cast<const ExplosiveBrick*> (brick.get())) {
                std::cout << "Am gasit un ExplosiveBrick la x=" <<explosive->getX() << std::endl;
            }
        }

        g1.update();
        g1.update();
        g1.spawnWave();
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

        //Test try catch
        Game test(100, 440, 0);
    } catch (const ConfigGresit& e) {
        std::cout << e.what() << std::endl;
    } catch (const GameException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
