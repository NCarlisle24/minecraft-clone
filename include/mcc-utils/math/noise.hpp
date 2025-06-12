#ifndef NOISE_HPP
#define NOISE_HPP

#include <ctime>
#include <cstdlib>
#include <iostream>

inline void initializeRandomSeed() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void perlinNoise(void* const* const data, const unsigned int &width, const unsigned int &height, const float &scale);

#endif