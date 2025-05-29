#ifndef STATE_HPP
#define STATE_HPP

#include <mcc-utils/helper.hpp>
#include <mcc-utils/rendering/renderer.hpp> // includes window, camera, and shader
#include <mcc-utils/rendering/texture.hpp>
#include <mcc-utils/world/block.hpp>
#include <mcc-utils/world/entities/entity.hpp>
#include <mcc-utils/world/entities/player.hpp>

#define INITIAL_SCR_WIDTH 1000
#define INITIAL_SCR_HEIGHT 500

#define DEFAULT_RENDER_DISTANCE 4 // in chunks

extern bool glfwIsInitialized;

unsigned int setupGLFW();
class State {
    public:
        float currentTime = 0.0f;
        float lastFrameTime = 0.0f;
        float deltaTime = 0.0f;
        float fps = 0.0f;
        double mouseX = 0.0f;
        double mouseY = 0.0f;
        bool firstMouseFocus = true;
        float aspectRatio = (float) INITIAL_SCR_WIDTH / (float) INITIAL_SCR_HEIGHT;
        int windowWidth = INITIAL_SCR_WIDTH;
        int windowHeight = INITIAL_SCR_HEIGHT;
        int renderDistance = DEFAULT_RENDER_DISTANCE;

        ~State();

        Renderer* renderer;
        Window* window;
        std::vector<Entity*> entities; // entities[0] is the player
        std::vector<Shader*> shaderPrograms;
        Texture2D* textures2D[MAX_TEXTURE_UNITS];

        Chunk* chunks;

        uint8_t activePlayerIndex = 0;
        uint8_t activeShaderIndex = 0;

        unsigned int init();
        void update();

    private:
        static void enableCapabilities();
        void processInput();
        void processCameraMovement();
        void processMouseInput();
};

#endif