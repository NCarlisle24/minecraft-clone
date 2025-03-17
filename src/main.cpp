#define STB_IMAGE_IMPLEMENTATION

#include <utils/helper.hpp>
#include <utils/window.hpp>
#include <utils/shader.hpp>
#include <utils/texture.hpp>
#include <utils/camera.hpp>
#include <utils/block.hpp>
#include <utils/renderer.hpp>
#include <utils/state.hpp>
#include <entities.hpp>

#define BASE_VERT_FILE_PATH "src/shaders/base.vert"
#define BASE_FRAG_FILE_PATH "src/shaders/base.frag"

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
    Texture2D* textureAtlas = new Texture2D("./src/textures/wall.jpg");

    state->textures2D[0] = textureAtlas;

    /* ======================================= entities ======================================= */

    Player* mainPlayer = new Player();
    Player* debugPlayer = new Player();

    Camera* mainCamera = new Camera(state->aspectRatio);
    Camera* debugCamera = new Camera(state->aspectRatio);

    mainPlayer->camera = mainCamera;
    debugPlayer->camera = debugCamera;

    state->entities.push_back(mainPlayer);
    state->entities.push_back(debugPlayer);

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