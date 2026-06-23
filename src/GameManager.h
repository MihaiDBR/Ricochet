#pragma once
#include <string>
#include <iostream>

class GameManager {
private:
    int highScore;
    int totalGamesPlayed;
    std::string playerName;

    GameManager();

public:
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    static GameManager& getInstance();

    void inregistreazaScor(int scor);
    void inregistreazaJoc();
    void seteazaNumeJucator(const std::string& nume);

    [[nodiscard]] int getHighScore() const;
    [[nodiscard]] int getTotalGamesPlayed() const;
    [[nodiscard]] const std::string& getPlayerName() const;

    friend std::ostream& operator<<(std::ostream& os, const GameManager& gm);
};