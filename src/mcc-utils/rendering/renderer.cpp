#include <mcc-utils/rendering/renderer.hpp>

const float testData[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

void toggleWireframeMode() {
    int polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    if (polygonMode == GL_FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

Renderer::Renderer() {
    if (glfwGetCurrentContext() == NULL) {
        std::cerr << "Error: No current OpenGL context." << std::endl;
        return;
    }

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // TBO
    glGenTextures(1, &blockPositionsTexture);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockVertices), blockVertices, GL_STATIC_DRAW);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(blockIndices), blockIndices, GL_STATIC_DRAW);

    // vertex attributes
    const int stride = sizeof(BlockVertex);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0); // position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3)); // texture coordinates
    glEnableVertexAttribArray(1);

    glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, stride, (void*)(sizeof(float) * 5)); // face index
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &blockPositionsTexture);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::render(Window* const &window, Camera* const &camera, Shader* const &shader) {
    window->setAsContext();
    glBindVertexArray(VAO);
    shader->use();

    // load matrix uniforms
    shader->setUniformMat4("view", camera->viewMatrix);
    shader->setUniformMat4("projection", camera->projectionMatrix);

    // load TBO data
    setActiveTextureUnit(0);

    unsigned int blockPositionsBuffer;
    glGenBuffers(1, &blockPositionsBuffer);
    glBindBuffer(GL_TEXTURE_BUFFER, blockPositionsBuffer);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(float) * 12, testData, GL_DYNAMIC_DRAW);

    glBindTexture(GL_TEXTURE_BUFFER, blockPositionsTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, blockPositionsBuffer);

    shader->setUniform1i("blockPositionTexture", 0);

    // debugging
    // float data[12];
    // glBindBuffer(GL_TEXTURE_BUFFER, blockPositionsBuffer);
    // glGetBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(data), data);

    // std::cout << std::endl;

    // draw stuff
    glDrawElementsInstanced(GL_TRIANGLES, BLOCK_INDICES_LENGTH, GL_UNSIGNED_INT, (void*)0, 4);
}
