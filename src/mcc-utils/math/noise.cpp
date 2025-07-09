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

    float dotProduct00, dotProduct10, dotProduct01, dotProduct11;
    int cornerIndices[4] = {0, 1, areaChunkLength + 1, areaChunkLength + 2};
    float interpolatedX1, interpolatedX2, noiseValue;
    int finalValue;

    for (int chunkIndex = 0; chunkIndex < numChunks; chunkIndex++) {
        // std::cerr << "Corner gradients for chunk " << chunkIndex << ": ";
        // std::cerr << "(" << cornerGradients[cornerIndices[0]].x << ", " << cornerGradients[cornerIndices[0]].y << ") | ";
        // std::cerr << "(" << cornerGradients[cornerIndices[1]].x << ", " << cornerGradients[cornerIndices[1]].y << ") | ";
        // std::cerr << "(" << cornerGradients[cornerIndices[2]].x << ", " << cornerGradients[cornerIndices[2]].y << ") | ";
        // std::cerr << "(" << cornerGradients[cornerIndices[3]].x << ", " << cornerGradients[cornerIndices[3]].y << ")";
        // std::cerr << std::endl;

        // std::cerr << "Chunk " << chunkIndex << " using corner indices: "
        //           << cornerIndices[0] << ", "
        //           << cornerIndices[1] << ", "
        //           << cornerIndices[2] << ", "
        //           << cornerIndices[3] << ", "
        //           << std::endl;

        
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                // only the first corner can have an offset of (0, 0), so check for that
                if (x == 0 && z == 0) {
                    dotProduct00 = 0.0f;
                } else {
                    dotProduct00 = glm::dot(cornerGradients[cornerIndices[0]], glm::vec2(x, z));
                }

                dotProduct10 = glm::dot(cornerGradients[cornerIndices[1]], glm::vec2(x - CHUNK_SIZE, z));
                dotProduct01 = glm::dot(cornerGradients[cornerIndices[2]], glm::vec2(x, z - CHUNK_SIZE));
                dotProduct11 = glm::dot(cornerGradients[cornerIndices[3]], glm::vec2(x - CHUNK_SIZE, z - CHUNK_SIZE));

                // TODO: use smooth step function for interpolation (linear for now)
                interpolatedX1 = ((CHUNK_SIZE - x) * dotProduct00 + x * dotProduct10) / CHUNK_SIZE;
                interpolatedX2 = ((CHUNK_SIZE - x) * dotProduct01 + x * dotProduct11) / CHUNK_SIZE;

                noiseValue = ((CHUNK_SIZE - z) * interpolatedX1 + z * interpolatedX2) / CHUNK_SIZE;
                // normalize to [-1, 1]
                noiseValue /= CHUNK_SIZE;
                noiseValue *= glm::root_two<float>(); // divide by sqrt(0.5) => multiply by sqrt(2)

                finalValue = static_cast<int>(noiseValue * scale);
                finalValue += WORLD_HEIGHT / 2;

                // std::cerr << "Chunk = " << chunkIndex << ", pos = (" << x << ", " << finalValue << ", " << z << ")," << "block index = " << getBlockIndex(x, finalValue, z) << std::endl;

                // if finalValue is out of bounds (ie scale is too large), we get a seg fault
                
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