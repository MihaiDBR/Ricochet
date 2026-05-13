#pragma once
#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit GameException(std::string msj) : mesaj(msj) {}
    const char* what() const noexcept override {
        return mesaj.c_str(); //convertim pt compatibilitate cu what
    }
};

class NivelInvalid: public GameException {
public:
    explicit NivelInvalid(int val)
    : GameException("Nivel invalid: " + std::to_string(val)) {}
};

class AfaraEcran: public GameException {
    public:
        explicit AfaraEcran(float x, float y)
            : GameException("Obiectul este in afara ecranului: " + std::to_string(x) + ", " + std::to_string(y)) {}
};

class ConfigGresit : public GameException {
    public:
        explicit ConfigGresit(const std::string& info)
            : GameException("Greseala la configuratie: " + info) {}
};