#define STB_IMAGE_IMPLEMENTATION
#include "utils.hpp"

#define INITIAL_SCR_WIDTH 1000
#define INITIAL_SCR_HEIGHT 500

#define BASE_VERT_FILE_PATH "src/shaders/base.vert"
#define BASE_FRAG_FILE_PATH "src/shaders/base.frag"

float currentTime = 0.0f;
float lastFrameTime = 0.0f;
float deltaTime = 0.0f;

float lastMouseX;
float lastMouseY;

bool firstMouseFocus = true;

void mouseCallback(GLFWwindow* window, double mouseX, double mouseY);
void keyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(Window* const &win);
void processInputForCamera(Window* const &window, Camera* const &camera);

Camera mainCamera;
Camera debugCamera;
Renderer* renderer;

int main() {
    /* ======================================= setup ======================================= */
    
    if (setupGLFW() == ERROR) {
        return 1;
    }

    Window* win = new Window(INITIAL_SCR_WIDTH, INITIAL_SCR_HEIGHT, "This is a title");
    win->setAsContext();

    // change input settings for mouse; implement in class?
    glfwSetInputMode(win->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // hide cursor and set to center of screen
    glfwSetCursorPosCallback(win->glfwWindow, mouseCallback);
    glfwSetKeyCallback(win->glfwWindow, keyboardInputCallback);

    /* ======================================= shaders ======================================= */

    Shader* baseShader = new Shader(BASE_VERT_FILE_PATH, BASE_FRAG_FILE_PATH);

    baseShader->use();
    baseShader->setUniform1i("textureAtlas", 0);
    baseShader->unuse();

    /* ======================================= textures ======================================= */

    setActiveTextureUnit(0);
    Texture2D* textureAtlas = new Texture2D("./src/textures/wall.jpg");

    /* ======================================= transforms ======================================= */

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    /* ======================================= main loop ======================================= */

    renderer = new Renderer();
    mainCamera.setAsActiveCamera();

    while (!(win->shouldClose())) {
        // pre-render setup
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;

        processInput(win);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // rendering
        renderer->render(win, getActiveCamera(), baseShader);

        win->swapBuffers();
        

        // post-render stuff
        glfwPollEvents();
        lastFrameTime = currentTime;
    }

    delete renderer;
    delete baseShader;
    delete textureAtlas;
    delete win;

    glfwTerminate();

    return 0;
}

void processInput(Window* const &window) {
    if (window->isPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window->glfwWindow, GLFW_TRUE);
    }

    Camera* camera = getActiveCamera();

    if (camera != NULL) {
        processInputForCamera(window, camera);
    }
}

void processInputForCamera(Window* const &window, Camera* const &camera) {
    // std::cout << "Camera position: (" << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << ")" << std::endl;
    // std::cout << "Camera direction angles: (" << camera->getDirectionAngles().x << ", " << camera->getDirectionAngles().y
    //           << ", " << camera->getDirectionAngles().z << ")" << std::endl;
    // std::cout << "Camera direction: (" << camera->getDirectionVector().x << ", " << camera->getDirectionVector().y
    //           << ", " << camera->getDirectionVector().z << ")" << std::endl;

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
        horizontalMovementVector += camera->left;
    }

    if (horizontalMovementVector != zeroVec3) {
        horizontalMovementVector = glm::normalize(horizontalMovementVector);
        camera->position += camera->horizontalMovementSpeed * deltaTime * horizontalMovementVector;
    }

    glm::vec3 verticalMovementVector = zeroVec3;

    if (window->isPressed(GLFW_KEY_SPACE)) {
        verticalMovementVector += upVec3;
    }
    if (window->isPressed(GLFW_KEY_LEFT_SHIFT)) {
       verticalMovementVector += downVec3;
    }

    camera->position += camera->verticalMovementSpeed * deltaTime * verticalMovementVector;
}

void mouseCallback(GLFWwindow* window, double mouseX, double mouseY) {
    if (firstMouseFocus) {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouseFocus = false;
    }

    const float mouseDeltaX = mouseX - lastMouseX;
    const float mouseDeltaY = lastMouseY - mouseY;

    Camera* camera = getActiveCamera();

    camera->rotateDirection(camera->mouseSensitivity * glm::vec3(mouseDeltaX, mouseDeltaY, 0.0f));

    // std::cout << "Facing direction (" << camera->getDirectionAngles().x << ", " << camera->getDirectionAngles().y
    //             << ", " << camera->getDirectionAngles().z << "), or (" << camera->getDirectionVector().x 
    //             << ", " << camera->getDirectionVector().y << ", " << camera->getDirectionVector().z << ")" << std::endl;

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

void keyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        Window::toggleWireframeMode();
    }
}