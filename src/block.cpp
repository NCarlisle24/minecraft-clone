#include <utils/block.hpp>

const BlockVertex blockVertices[BLOCK_VERTICES_LENGTH] = {
    // front face
    { 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  NEG_Z },
    { 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  NEG_Z },
    { 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  NEG_Z },
    { 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,  NEG_Z },

    // back face
    { 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  POS_Z },
    { 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  POS_Z },
    { 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  POS_Z },
    { 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  POS_Z },
    
    // left face
    { 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  NEG_X },
    { 0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  NEG_X },
    { 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  NEG_X },
    { 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  NEG_X },

    // right face
    { 1.0f, 0.0f, 1.0f,  0.0f, 0.0f,  POS_X },
    { 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  POS_X },
    { 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  POS_X },
    { 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,  POS_X },

    // bottom face
    { 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  NEG_Y },
    { 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  NEG_Y },
    { 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  NEG_Y },
    { 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  NEG_Y },

    // top face
    { 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  POS_Y },
    { 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  POS_Y },
    { 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  POS_Y },
    { 1.0f, 1.0f, 0.0f,  1.0f, 1.0f,  POS_Y },
};

const unsigned int blockIndices[BLOCK_INDICES_LENGTH] {
    0, 1, 2, 2, 1, 3,
    4, 5, 6, 6, 5, 7,
    8, 9, 10, 10, 9, 11,
    12, 13, 14, 14, 13, 15,
    16, 17, 18, 18, 17, 19,
    20, 21, 22, 22, 21, 23
};