#include "Game.h"
#include "HardBrick.h"
#include "ExplosiveBrick.h"
#include "GameException.h"
#include "GameManager.h"
#include "ObjectPool.h"
#include "BrickFactory.h"
#include "Utils.h"
#include "Ball.h"
#include <cassert>
#include <iostream>

int main() {
    try {
        // Singleton - GameManager
        GameManager& gm = GameManager::getInstance();
        gm.seteazaNumeJucator("DBR");
        gm.inregistreazaJoc();
        std::cout << gm << std::endl;

        Game g1(680, 440, 3);
        g1.spawnWave();
        g1.spawnWave();
        g1.spawnWave();
        std::cout << g1 << std::endl;

        // Dynamic_cast
        for (const auto& brick : g1.getBricks()) {
            if (const auto* hard = dynamic_cast<const HardBrick*>(brick.get())) {
                std::cout << "Am gasit un HardBrick la x=" << hard->getX() << std::endl;
            } else if (const auto* explosive = dynamic_cast<const ExplosiveBrick*>(brick.get())) {
                std::cout << "Am gasit un ExplosiveBrick la x=" << explosive->getX() << std::endl;
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

        // CC si op=
        Game g2(g1);
        assert(g1 == g2);
        std::cout << "CC: Copiere corecta" << std::endl;

        Game g3(680, 440, 5);
        g3 = g1;
        assert(g1 == g3);
        std::cout << "Op=: Copiere corecta" << std::endl;

        // Singleton - inregistrare scor
        gm.inregistreazaScor(150);
        gm.inregistreazaScor(80);
        std::cout << "High score: " << gm.getHighScore() << std::endl;
        std::cout << gm << std::endl;

        // Factory pattern
        auto brickTest = BrickFactory::create("hard", 100, 50, 60, 20);
        std::cout << "Factory a creat: " << *brickTest << std::endl;

        // ObjectPool<Ball> - prima instantiere template
        ObjectPool<Ball> poolBile(5);
        poolBile.adauga(Ball(100, 200, 3, -3, 6));
        poolBile.adauga(Ball(200, 200, -2, -4, 6));
        std::cout << "Pool bile: " << poolBile << std::endl;
        Ball bilaPrimita = poolBile.preia();
        std::cout << "Bila preluata: " << bilaPrimita << std::endl;
        std::cout << "Pool dupa preluare: " << poolBile << std::endl;

        // ObjectPool<int> - a doua instantiere template
        ObjectPool<int> poolScoruri(10);
        poolScoruri.adauga(100);
        poolScoruri.adauga(250);
        poolScoruri.adauga(50);
        int scorTop = poolScoruri.preia();
        std::cout << "Scor preluat din pool: " << scorTop << std::endl;
        std::cout << "Pool scoruri: " << poolScoruri << std::endl;

        // Functie template clamp - instantiere cu float
        float pozitieX = 750.0f;
        float pozitieClampata = clamp(pozitieX, 0.0f, 680.0f);
        std::cout << "Pozitie originala: " << pozitieX << ", dupa clamp: " << pozitieClampata << std::endl;

        // Functie template clamp - instantiere cu int
        int vietiNoi = -2;
        int vietiClampate = clamp(vietiNoi, 0, 5);
        std::cout << "Vieti originale: " << vietiNoi << ", dupa clamp: " << vietiClampate << std::endl;

        // Test exceptie
        Game test(100, 440, 0);

    } catch (const ConfigGresit& e) {
        std::cout << e.what() << std::endl;
    } catch (const GameException& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Au fost create: " << Brick::getTotBricks() << " nr de brick-uri" << std::endl;

    return 0;
}