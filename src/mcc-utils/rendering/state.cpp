#include <mcc-utils/rendering/state.hpp>

bool glfwIsInitialized = false;

static void defaultGlfwErrorCallback(int error, const char* msg) {
    std::cerr << "[" << error << "] " << msg << std::endl;
}

unsigned int setupGLFW() {
    glfwSetErrorCallback(defaultGlfwErrorCallback);

    if (!glfwInit()) {
        return ERROR;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    glfwIsInitialized = true;

    return SUCCESS;
}

void State::processCameraMovement() {
    // std::cout << "Camera position: (" << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << ")" << std::endl;
    // std::cout << "Camera direction angles: (" << camera->getDirectionAngles().x << ", " << camera->getDirectionAngles().y
    //           << ", " << camera->getDirectionAngles().z << ")" << std::endl;

    Player* player = (Player*)entities[activePlayerIndex];

    // std::cout << "Camera direction: (" << player->camera->getDirection().x << ", " << player->camera->getDirection().y
    //           << ", " << player->camera->getDirection().z << "), Angles: (" << player->camera->getDirectionAngles().x 
    //           << ", " << player->camera->getDirectionAngles().y << ", " << player->camera->getDirectionAngles().z 
    //           << ")" << std::endl;

    // std::cout << "Player direction: (" << player->getDirection().x << ", " << player->getDirection().y
    //           << ", " << player->getDirection().z << "), Angles: (" << player->getDirectionAngles().x 
    //           << ", " << player->getDirectionAngles().y << ", " << player->getDirectionAngles().z 
    //           << ")" << std::endl;

    glm::vec3 horizontalMovementVector = zeroVec3;

    if (window->isPressed(GLFW_KEY_W)) {
        horizontalMovementVector += player->getHorizontalDirection();
    }
    if (window->isPressed(GLFW_KEY_S)) {
        horizontalMovementVector -= player->getHorizontalDirection();
    }
    if (window->isPressed(GLFW_KEY_D)) {
        horizontalMovementVector += player->getRightDirection();
    }
    if (window->isPressed(GLFW_KEY_A)) {
        horizontalMovementVector -= player->getRightDirection();
    }

    if (horizontalMovementVector != zeroVec3) {
        horizontalMovementVector = glm::normalize(horizontalMovementVector);
        player->move(player->horizontalMovementSpeed * State::deltaTime * horizontalMovementVector);
    }

    glm::vec3 verticalMovementVector = zeroVec3;

    if (window->isPressed(GLFW_KEY_SPACE)) {
        verticalMovementVector += upVec3;
    }
    if (window->isPressed(GLFW_KEY_LEFT_SHIFT)) {
       verticalMovementVector += downVec3;
    }

    if (verticalMovementVector != zeroVec3) {
        player->move(player->verticalMovementSpeed * State::deltaTime * verticalMovementVector);
    }
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
static void keyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_F:
                toggleWireframeMode();
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    State* state = (State*)glfwGetWindowUserPointer(window);

    state->windowWidth = width;
    state->windowHeight = height;
    state->aspectRatio = (float) width / (float) height;

    for (size_t i = 0; i < state->entities.size(); i++) {
        state->entities[i]->camera->updateProjectionMatrix(state->aspectRatio);
    }
}

static void mousePositionCallback(GLFWwindow* window, double newMouseX, double newMouseY) {
    State* state = (State*)glfwGetWindowUserPointer(window);

    if (state->firstMouseFocus) {
        state->mouseX = newMouseX;
        state->mouseY = newMouseY;
        state->firstMouseFocus = false;
    }

    Player* player = (Player*)(state->entities[state->activePlayerIndex]);

    glm::vec3 mouseDelta = glm::vec3(newMouseX - state->mouseX, state->mouseY - newMouseY, 0.0f);
    
    mouseDelta *= player->mouseCameraSensitivity;
    player->rotateDirection(mouseDelta);

    state->mouseX = newMouseX;
    state->mouseY = newMouseY;
}

State::~State() {
    delete renderer;
    delete window;
}

unsigned int State::init() {
    if (!glfwIsInitialized) {
        std::cerr << "Error: GLFW is not initialized." << std::endl;
        return ERROR;
    }

    window = new Window(INITIAL_SCR_WIDTH, INITIAL_SCR_HEIGHT, "This is a title");
    if (window->glfwWindow == NULL) {
        return ERROR;
    }

    renderer = new Renderer();

    window->setAsContext();
    enableCapabilities();

    glfwSetInputMode(window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // hide cursor and set to center of screen
    glfwSetFramebufferSizeCallback(window->glfwWindow, framebufferSizeCallback);
    glfwSetKeyCallback(window->glfwWindow, keyboardInputCallback);
    glfwSetCursorPosCallback(window->glfwWindow, mousePositionCallback);

    window->setUserPointer(this);

    return SUCCESS;
}

void State::update() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    fps = 1.0f / deltaTime;
    processInput();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->render(window, entities[activePlayerIndex]->camera, shaderPrograms[activeShaderIndex]);

    window->swapBuffers();

    glfwPollEvents();
    lastFrameTime = currentTime;
}

void State::processInput() {
    processCameraMovement();
}

void State::enableCapabilities() {
    glEnable(GL_DEPTH_TEST);
}