#pragma once

template <typename T>
T clamp(T valoare, T minim, T maxim) {
    if (valoare < minim) return minim;
    if (valoare > maxim) return maxim;
    return valoare;
}