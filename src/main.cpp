#define STB_IMAGE_IMPLEMENTATION // only do ONCE in the entire project
#include "../internal/main-utils.hpp"

#define BASE_VERT_FILE_PATH "./assets/shaders/base.vert"
#define BASE_FRAG_FILE_PATH "./assets/shaders/base.frag"
#define TEXTURE_ATLAS_FILE_PATH "./assets/textures/wall.jpg"

State* state;

int main() {
    /* ======================================= setup ======================================= */

    if (setupGLFW() == ERROR) {
        std::cerr << "Error: Failed to initialize GLFW." << std::endl;
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
    Texture2D* textureAtlas = new Texture2D(TEXTURE_ATLAS_FILE_PATH);

    state->textures2D[0] = textureAtlas;

    /* ======================================= entities ======================================= */

    Camera* mainCamera = new Camera(state->aspectRatio);
    Camera* debugCamera = new Camera(state->aspectRatio);

    Player* mainPlayer = new Player(mainCamera);
    Player* debugPlayer = new Player(debugCamera);

    state->entities.push_back(mainPlayer);
    state->entities.push_back(debugPlayer);

    mainPlayer->setPosition(glm::vec3(0.0f, static_cast<float>(WORLD_HEIGHT / 2), 0.0f));

    /* ======================================= main loop ======================================= */

    glfwSwapInterval(0); // disable vsync

    while (!(state->window->shouldClose())) {
        state->update();
    }

    std::cout << "FPS at closing time: " << state->fps << std::endl;

    delete baseShader;
    delete textureAtlas;
    delete mainCamera;
    delete debugCamera;
    delete state;

    glfwTerminate();

    return 0;
}