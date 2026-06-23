#include "GameManager.h"

GameManager::GameManager() : highScore(0), totalGamesPlayed(0), playerName("Anonim") {}

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

void GameManager::inregistreazaScor(int scor) {
    if (scor > highScore)
        highScore = scor;
}

void GameManager::inregistreazaJoc() {
    totalGamesPlayed++;
}

void GameManager::seteazaNumeJucator(const std::string& nume) {
    playerName = nume;
}

int GameManager::getHighScore() const { return highScore; }
int GameManager::getTotalGamesPlayed() const { return totalGamesPlayed; }
const std::string& GameManager::getPlayerName() const { return playerName; }

std::ostream& operator<<(std::ostream& os, const GameManager& gm) {
    os << "GameManager [jucator=" << gm.playerName
       << ", highScore=" << gm.highScore
       << ", jocuriJucate=" << gm.totalGamesPlayed << "]";
    return os;
}