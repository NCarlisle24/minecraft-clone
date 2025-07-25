#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <mcc-utils/helper.hpp>

#define CHUNK_SIZE 16
#define WORLD_HEIGHT 256

#define BLOCK_VERTICES_LENGTH 24
#define BLOCK_INDICES_LENGTH 36

typedef enum {
    DIRT, // 0
    GRASS, // 1
    STONE, // etc.
    AIR = 255
} BlockId;
typedef enum {
    POS_X,
    NEG_X,
    POS_Y,
    NEG_Y,
    POS_Z,
    NEG_Z,
    NO_DIRECTION
} AxisDirection;

typedef struct {
    float x, y, z;
    float u, v;
    AxisDirection faceDirection;
} BlockVertex;

typedef struct {
    BlockId id;
    AxisDirection horizontalOrientation; // x/z direction
    AxisDirection verticalOrientation; // y direction
} Block;

typedef struct {
    int x, z; // world space
    Block blockData[CHUNK_SIZE * CHUNK_SIZE * WORLD_HEIGHT];
} Chunk;

extern const BlockVertex blockVertices[BLOCK_VERTICES_LENGTH];
extern const unsigned int blockIndices[BLOCK_INDICES_LENGTH];

// (x, y, z) -> local coordinates relative to the chunk's (NEG_X, NEG_Y, NEG_Z) corner
constexpr size_t getBlockIndex(int x, int y, int z) {
    return (y * CHUNK_SIZE * CHUNK_SIZE) + (z * CHUNK_SIZE) + x;
}

#endif