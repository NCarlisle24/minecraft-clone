#define STB_IMAGE_IMPLEMENTATION
#include <utils/setup.hpp>
#include <utils/shader.hpp>
#include <utils/texture.hpp>
#include <utils/camera.hpp>

#define INITIAL_SCR_WIDTH 1000
#define INITIAL_SCR_HEIGHT 500

#define DEGREE_FOV 45.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f

#define NUM_VAOS 1
#define NUM_VBOS 1
#define NUM_EBOS 1

#define BASE_VERT_FILE_PATH "src/shaders/base.vert"
#define BASE_FRAG_FILE_PATH "src/shaders/base.frag"

int screenWidth = INITIAL_SCR_WIDTH;
int screenHeight = INITIAL_SCR_HEIGHT;

float currentTime = 0.0f;
float lastFrameTime = 0.0f;
float deltaTime = 0.0f;

float lastMouseX;
float lastMouseY;

bool firstMouseFocus = true;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double mouseX, double mouseY);
void keyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(Window* &win);
void processInputForCamera(Window* &window, Camera* &camera);

Camera camera1;
Camera camera2;

int main() {
    /* ======================================= setup ======================================= */
    
    if (setupGLFW() == ERROR) {
        return 1;
    }

    Window* win = new Window(INITIAL_SCR_WIDTH, INITIAL_SCR_HEIGHT, "This is a title");
    win->setAsContext();
    win->setFramebufferSizeCallback(frameBufferSizeCallback);

    // change input settings for mouse; implement in class?
    glfwSetInputMode(win->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // hide cursor and set to center of screen
    glfwSetCursorPosCallback(win->glfwWindow, mouseCallback);
    glfwSetKeyCallback(win->glfwWindow, keyboardInputCallback);

    /* ======================================= buffers ======================================= */

    float vertices[] = {
        // front face
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,

        // back face
        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 1.0f
    };

    unsigned int indices[] {
        // front face
        0, 1, 2,  2, 1, 3,
        // left face
        4, 0, 6,  6, 0, 2,
        // back face
        4, 5, 6,  6, 5, 7,
        // right face
        1, 5, 3,  3, 5, 7
    };

    unsigned int VAO[NUM_VAOS];

    glGenVertexArrays(NUM_VAOS, VAO);
    glBindVertexArray(VAO[0]);

    unsigned int EBO[NUM_EBOS];

    glGenBuffers(NUM_EBOS, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO[NUM_VBOS];

    glGenBuffers(NUM_VBOS, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const int stride = sizeof(float)*5;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    /* ======================================= shaders ======================================= */

    Shader* baseShader = new Shader(BASE_VERT_FILE_PATH, BASE_FRAG_FILE_PATH);

    baseShader->use();
    baseShader->setUniform1i("wallTexture", 0);
    baseShader->setUniform1i("smileTexture", 1);
    baseShader->unuse();

    /* ======================================= textures ======================================= */

    setActiveTextureUnit(0);

    Texture2D* doorTexture = new Texture2D("./src/textures/wall.jpg");

    setActiveTextureUnit(1);

    setTextureVerticalOrientation(FLIP);
    Texture2D* smileTexture = new Texture2D("./src/textures/smile.png");
    setTextureVerticalOrientation(NORMAL);

    /* ======================================= transforms ======================================= */

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    /* ======================================= main loop ======================================= */

    glBindVertexArray(VAO[0]);
    baseShader->use();
    camera1.setAsActiveCamera();

    while (!(win->shouldClose())) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrameTime;

        processInput(win);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // model = glm::rotate(identityMat4, (float)glfwGetTime(), glm::vec3(1.0f, 0.5f, 0.0f));
        model = glm::translate(identityMat4, glm::vec3(0.0f, 0.0f, -2.0f));
        view = getActiveCamera()->getViewMatrix();
        projection = glm::perspective(glm::radians(DEGREE_FOV), (float)screenWidth / (float)screenHeight, NEAR_PLANE, FAR_PLANE);

        baseShader->setUniformMat4("model", model);
        baseShader->setUniformMat4("view", view);
        baseShader->setUniformMat4("projection", projection);

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);

        win->swapBuffers();
        glfwPollEvents();

        lastFrameTime = currentTime;
    }

    delete baseShader;
    delete doorTexture;
    delete smileTexture;

    glDeleteBuffers(NUM_VBOS, VBO);
    glDeleteBuffers(NUM_EBOS, EBO);
    glDeleteVertexArrays(NUM_VAOS, VAO);

    glfwTerminate();

    return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
}

void processInput(Window* &window) {
    if (window->isPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window->glfwWindow, GLFW_TRUE);
    }

    Camera* camera = getActiveCamera();

    if (camera != NULL) {
        processInputForCamera(window, camera);
    }
}

void processInputForCamera(Window* &window, Camera* &camera) {
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

    Camera* camera = Camera::currentlyActiveCamera;

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