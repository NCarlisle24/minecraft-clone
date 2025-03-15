#include <utils/state.hpp>

bool glfwIsInitialized = false;

int setupGLFW() {
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

void defaultGlfwErrorCallback(int error, const char* msg) {
    std::cerr << "[" << error << "] " << msg << std::endl;
}

void State::processCameraMovement() {
    // std::cout << "Camera position: (" << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << ")" << std::endl;
    // std::cout << "Camera direction angles: (" << camera->getDirectionAngles().x << ", " << camera->getDirectionAngles().y
    //           << ", " << camera->getDirectionAngles().z << ")" << std::endl;
    // std::cout << "Camera direction: (" << camera->getDirectionVector().x << ", " << camera->getDirectionVector().y
    //           << ", " << camera->getDirectionVector().z << ")" << std::endl;

    Camera* camera = cameras[activeCameraIndex];

    glm::vec3 horizontalMovementVector = zeroVec3;

    if (window->isPressed(GLFW_KEY_W)) {
        horizontalMovementVector += camera->getHorizontalDirectionVector();
    }
    if (window->isPressed(GLFW_KEY_S)) {
        horizontalMovementVector -= camera->getHorizontalDirectionVector();
    }
    if (window->isPressed(GLFW_KEY_D)) {
        horizontalMovementVector += camera->right;
    }
    if (window->isPressed(GLFW_KEY_A)) {
        horizontalMovementVector -= camera->right;
    }

    if (horizontalMovementVector != zeroVec3) {
        horizontalMovementVector = glm::normalize(horizontalMovementVector);
        camera->move(camera->horizontalMovementSpeed * State::deltaTime * horizontalMovementVector);
    }

    glm::vec3 verticalMovementVector = zeroVec3;

    if (window->isPressed(GLFW_KEY_SPACE)) {
        verticalMovementVector += upVec3;
    }
    if (window->isPressed(GLFW_KEY_LEFT_SHIFT)) {
       verticalMovementVector += downVec3;
    }

    if (verticalMovementVector != zeroVec3) {
        camera->move(camera->verticalMovementSpeed * State::deltaTime * verticalMovementVector);
    }
}

void keyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    State* state = (State*)glfwGetWindowUserPointer(window);

    state->windowWidth = width;
    state->windowHeight = height;
    state->aspectRatio = (float) width / (float) height;

    for (int i = 0; i < state->cameras.size(); i++) {
        state->cameras[i]->updateProjectionMatrix(state->aspectRatio);
    }
}

void mousePositionCallback(GLFWwindow* window, double newMouseX, double newMouseY) {
    State* state = (State*)glfwGetWindowUserPointer(window);

    if (state->firstMouseFocus) {
        state->mouseX = newMouseX;
        state->mouseY = newMouseY;
        state->firstMouseFocus = false;
    }

    Camera* camera = state->cameras[state->activeCameraIndex];

    glm::vec3 mouseDelta = glm::vec3(newMouseX - state->mouseX, state->mouseY - newMouseY, 0.0f);
    
    if (camera != NULL) {
        mouseDelta *= camera->mouseSensitivity;
        camera->rotateDirection(mouseDelta);
    }

    state->mouseX = newMouseX;
    state->mouseY = newMouseY;
}

State::~State() {
    delete renderer;
    delete window;
}

int State::init() {
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

    renderer->render(window, cameras[activeCameraIndex], shaderPrograms[activeShaderIndex]);

    window->swapBuffers();

    glfwPollEvents();
    lastFrameTime = currentTime;
}

void State::processInput() {
    Camera* camera = cameras[activeCameraIndex];

    if (camera != NULL) {
        processCameraMovement();
    }
}

void State::enableCapabilities() {
    glEnable(GL_DEPTH_TEST);
}