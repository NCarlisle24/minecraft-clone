#include <mcc-utils/math/noise.hpp>

glm::vec2 generateRandom2dUnitVector() {
    float angle = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * glm::two_pi<float>();
    return glm::vec2(cos(angle), sin(angle));
}

// 1. Generate a random 2D vector at every chunk corner (x, z)
// 2. For each block in a chunk, calculate its offset from each chunk corner (just the x/z coordinates)
// 3. Calculate the dot products of each offset with the corresponding random vector
// 4. Interpolate the dot products based on how close the block is to each corner
// 5. Add a block at this interpolated value
// 6. Repeat for each block and chunk
// NOTE: chunks should be a 1D array of Chunk objects stored in x-major order. (increment index by 1 to move along x-axis, increment by areaChunkLength to move along z-axis)
void generateChunks(Chunk* const &chunks, const int &areaChunkLength, const float &scale) {
    const int numChunks = areaChunkLength * areaChunkLength;
    const int numCorners = (areaChunkLength + 1) * (areaChunkLength + 1);

    glm::vec2 cornerGradients[numCorners];

    for (int i = 0; i < numCorners; i++) {
        cornerGradients[i] = generateRandom2dUnitVector();
    }

    float dotProducts[4];
    int cornerIndices[4] = {0, 1, areaChunkLength + 1, areaChunkLength + 2};
    float interpolatedX1, interpolatedX2;
    int finalValue;

    for (int chunkIndex = 0; chunkIndex < numChunks; chunkIndex++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                if (x == 0 && z == 0) {
                    dotProducts[0] = 0.0f;
                } else {
                    dotProducts[0] = glm::dot(cornerGradients[cornerIndices[0]], glm::normalize(glm::vec2(x, z)));
                }
                
                if (x == CHUNK_SIZE - 1 && z == 0) {
                    dotProducts[1] = 0.0f;
                } else {
                    dotProducts[1] = glm::dot(cornerGradients[cornerIndices[1]], glm::normalize(glm::vec2(x - (CHUNK_SIZE - 1), z)));
                }

                if (x == 0 && z == CHUNK_SIZE - 1) {
                    dotProducts[2] = 0.0f;
                } else {
                    dotProducts[2] = glm::dot(cornerGradients[cornerIndices[2]], glm::normalize(glm::vec2(x, z - (CHUNK_SIZE - 1))));
                }

                if (x == CHUNK_SIZE - 1 && z == CHUNK_SIZE - 1) {
                    dotProducts[3] = 0.0f;
                } else {
                    dotProducts[3] = glm::dot(cornerGradients[cornerIndices[3]], glm::normalize(glm::vec2(x - (CHUNK_SIZE - 1), z - (CHUNK_SIZE - 1))));
                }

                // move dot products to range [0, 1]
                // TODO: this is erroneous because we need to move the range of the final value, not the dot products
                // need to map y=0 to "middle" of the chunk, where y=CHUNK_HEIGHT/2 is top/bottom
                for (auto &dotProduct : dotProducts) {
                    dotProduct = (dotProduct + 1.0f) * 0.5f;
                }

                // TODO: use smooth step function for interpolation (linear for now)
                interpolatedX1 = ((CHUNK_SIZE - x) * dotProducts[0] + x * dotProducts[1]) / CHUNK_SIZE;
                interpolatedX2 = ((CHUNK_SIZE - x) * dotProducts[2] + x * dotProducts[3]) / CHUNK_SIZE;
                finalValue = static_cast<int>(scale * ((CHUNK_SIZE - z) * interpolatedX1 + z * interpolatedX2) / CHUNK_SIZE);
                
                // std::cerr << "Chunk = " << chunkIndex << ", pos = (" << x << ", " << finalValue << ", " << z << ")," << "block index = " << getBlockIndex(x, finalValue, z) << std::endl;
                
                chunks[chunkIndex].blockData[getBlockIndex(x, finalValue, z)] = {
                    .id = DIRT,
                    .horizontalOrientation = NO_DIRECTION,
                    .verticalOrientation = NO_DIRECTION
                };

                // fill rest of column with air
                for (int y = 0; y < finalValue; y++) {
                    chunks[chunkIndex].blockData[getBlockIndex(x, y, z)] = {
                        .id = AIR,
                        .horizontalOrientation = NO_DIRECTION,
                        .verticalOrientation = NO_DIRECTION
                    };
                }

                for (int y = finalValue + 1; y < WORLD_HEIGHT; y++) {
                    chunks[chunkIndex].blockData[getBlockIndex(x, y, z)] = {
                        .id = AIR,
                        .horizontalOrientation = NO_DIRECTION,
                        .verticalOrientation = NO_DIRECTION
                    };
                }
            }
        }

        // if we are at the end of chunks along the x-axis, increment
        // the corner indices twice to move to the next row
        // otherwise, increment as normal
        if (chunkIndex % areaChunkLength == areaChunkLength - 1) {
            for (int i = 0; i < 4; i++) {
                cornerIndices[i] += 2;
            }
        } else {
            for (int i = 0; i < 4; i++) {
                cornerIndices[i]++;
            }
        }
    }
}