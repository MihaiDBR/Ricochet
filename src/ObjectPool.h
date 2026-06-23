#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class ObjectPool {
private:
    std::vector<T> obiecteDisponibile;
    std::vector<T> obiecteActive;
    int maxDimensiune;

public:
    explicit ObjectPool(int maxDim) : maxDimensiune(maxDim) {}

    void adauga(const T& obiect) {
        if (static_cast<int>(obiecteDisponibile.size()) >= maxDimensiune)
            throw std::overflow_error("Pool-ul este plin");
        obiecteDisponibile.push_back(obiect);
    }

    T preia() {
        if (obiecteDisponibile.empty())
            throw std::underflow_error("Pool-ul este gol");
        T obiect = obiecteDisponibile.back();
        obiecteDisponibile.pop_back();
        obiecteActive.push_back(obiect);
        return obiect;
    }

    void returneaza(const T& obiect) {
        obiecteDisponibile.push_back(obiect);
        for (auto it = obiecteActive.begin(); it != obiecteActive.end(); ++it) {
            if (*it == obiect) {
                obiecteActive.erase(it);
                break;
            }
        }
    }

    [[nodiscard]] int getDisponibile() const {
        return static_cast<int>(obiecteDisponibile.size());
    }

    [[nodiscard]] int getActive() const {
        return static_cast<int>(obiecteActive.size());
    }

    friend std::ostream& operator<<(std::ostream& os, const ObjectPool<T>& pool) {
        os << "ObjectPool [disponibile=" << pool.obiecteDisponibile.size()
           << ", active=" << pool.obiecteActive.size()
           << ", maxDim=" << pool.maxDimensiune << "]";
        return os;
    }
};