#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <mcc-utils/helper.hpp>

#define DEFAULT_DEGREE_FOV 70.0f
#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 100.0f

class Camera {
    public:
        float fov = DEFAULT_DEGREE_FOV;
        float nearPlane = DEFAULT_NEAR_PLANE;
        float farPlane = DEFAULT_FAR_PLANE;

        glm::mat4 translationViewMatrix = identityMat4;
        glm::mat4 rotationViewMatrix = identityMat4;
        glm::mat4 viewMatrix = identityMat4;
        glm::mat4 projectionMatrix = identityMat4;

        Camera(const float &aspectRatio = 1.0f);

        glm::vec3 getDirection();
        glm::vec3 getHorizontalDirection();
        glm::vec3 getDirectionAngles();
        glm::vec3 getPosition();

        void updateProjectionMatrix(const float &aspectRatio);

        void setDirectionDirect(const glm::vec3 &newDirection, const glm::vec3 &newHorizontalDirection, const glm::vec3 &newDirectionAngles, const AngleType &angleType = DEGREES);
        void setDirection(const glm::vec3 &newDirection);
        void setDirectionAngles(const glm::vec3 &newDirectionAngles, const AngleType &angleType = DEGREES);
        void setPosition(const glm::vec3 &newPosition);
    
    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f); // x, y, and z
        glm::vec3 horizontalDirection = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 directionAngles = glm::vec3(90.0f, 0.0f, 0.0f); // yaw, pitch, and roll
        void updateDirectionFromAngles(); // clamps yaw/pitch and sets direction

        void updateTranslationViewMatrix();
        void updateRotationViewMatrix();
        void updateViewMatrix();

        glm::mat4 calculateProjectionMatrix(const float &aspectRatio);
};

#endif