#define STB_IMAGE_IMPLEMENTATION
#include "utils.hpp"

#define BASE_VERT_FILE_PATH "src/shaders/base.vert"
#define BASE_FRAG_FILE_PATH "src/shaders/base.frag"

State* state;

int main() {
    /* ======================================= setup ======================================= */
    
    if (setupGLFW() == ERROR) {
        std::cout << "Error: Failed to initialize GLFW." << std::endl;
        return 1;
    }

    state = new State();

    if (state->init() == ERROR) {
        return 1;
    }

    /* ======================================= shaders ======================================= */

    Shader* baseShader = new Shader(BASE_VERT_FILE_PATH, BASE_FRAG_FILE_PATH);

    baseShader->use();
    baseShader->setUniform1i("textureAtlas", 0);
    baseShader->unuse();

    state->shaderPrograms.push_back(baseShader);

    /* ======================================= textures ======================================= */

    setActiveTextureUnit(0);
    Texture2D* textureAtlas = new Texture2D("./src/textures/wall.jpg");

    state->textures2D[0] = textureAtlas;

    /* ======================================= cameras ======================================= */

    Camera* mainCamera = new Camera(state->aspectRatio);
    Camera* debugCamera = new Camera(state->aspectRatio);

    state->cameras.push_back(mainCamera);
    state->cameras.push_back(debugCamera);

    /* ======================================= main loop ======================================= */

    glfwSwapInterval(0); // disable vsync

    while (!(state->window->shouldClose())) {
        state->update();
    }

    std::cout << "FPS: " << state->fps << std::endl;

    delete baseShader;
    delete textureAtlas;
    delete mainCamera;
    delete debugCamera;
    delete state;

    glfwTerminate();

    return 0;
}