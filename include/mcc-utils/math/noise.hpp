#ifndef NOISE_HPP
#define NOISE_HPP

#include <mcc-utils/world/block.hpp>
#include <ext/glm/glm.hpp>
#include <ext/glm/gtc/constants.hpp>
#include <iostream>

void generateChunks(Chunk* const &chunks, const int &areaChunkLength, const float &scale);

#endif