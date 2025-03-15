#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utils/helper.hpp>

#define DEFAULT_CAMERA_HORIZONTAL_MOVEMENT_SPEED 7.0f
#define DEFAULT_CAMERA_VERTICAL_MOVEMENT_SPEED 5.0f

#define DEFAULT_MOUSE_CAMERA_SENSITIVITY 0.1f

#define DEFAULT_DEGREE_FOV 45.0f
#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 100.0f

class Camera {
    public:
        static float mouseSensitivity;
        static float horizontalMovementSpeed;
        static float verticalMovementSpeed;
        float fov = DEFAULT_DEGREE_FOV;
        float nearPlane = DEFAULT_NEAR_PLANE;
        float farPlane = DEFAULT_FAR_PLANE;

        glm::vec3 right; // +x

        glm::mat4 translationViewMatrix = identityMat4;
        glm::mat4 rotationViewMatrix = identityMat4;
        glm::mat4 viewMatrix = identityMat4;
        glm::mat4 projectionMatrix = identityMat4;

        Camera(const float &aspectRatio = 1.0f);
        void setDirectionVector(const glm::vec3 &newDirection);
        void setDirectionAngles(const glm::vec3 &newDirectionAngles, const bool &inRadians = false);
        void rotateDirection(const glm::vec3 &deltaAngles, const bool &inRadians = false);
        void move(const glm::vec3 &movementVector);
        void setPosition(const glm::vec3 &newPosition);

        glm::vec3 getDirectionVector();
        glm::vec3 getHorizontalDirectionVector();
        glm::vec3 getDirectionAngles();
        glm::vec3 getPosition();

        void updateProjectionMatrix(const float &aspectRatio);
    
    private:
        glm::vec3 position;
        glm::vec3 direction; // x, y, and z
        glm::vec3 horizontalDirection;
        glm::vec3 directionAngles; // yaw, pitch, and roll
        void updateDirectionVectors();
        void updateAxisVectors();

        void updateTranslationViewMatrix();
        void updateRotationViewMatrix();
        void updateViewMatrix();

        glm::mat4 calculateProjectionMatrix(const float &aspectRatio);
};

#endif