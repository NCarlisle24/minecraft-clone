#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utils/setup.hpp>

#define DEFAULT_CAMERA_HORIZONTAL_MOVEMENT_SPEED 7.0f
#define DEFAULT_CAMERA_VERTICAL_MOVEMENT_SPEED 5.0f

#define DEFAULT_MOUSE_CAMERA_SENSITIVITY 0.1f

#define DEFAULT_DEGREE_FOV 45.0f
#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 100.0f

class Camera {
    public:
        static Camera* activeCamera;
        static float horizontalMovementSpeed;
        static float verticalMovementSpeed;
        static float mouseSensitivity;
        static float fov;
        static float nearPlane;
        static float farPlane;

        glm::vec3 right;
        glm::vec3 left;
        glm::vec3 up;
        glm::vec3 down;

        glm::vec3 position;

        Camera();
        void setDirectionVector(const glm::vec3 &newDirection);
        void setDirectionAngles(const glm::vec3 &newDirectionAngles, const bool &inRadians = false);
        void rotateDirection(const glm::vec3 &deltaAngles, const bool &inRadians = false);
        glm::vec3 getDirectionVector();
        glm::vec3 getHorizontalDirectionVector();
        glm::vec3 getDirectionAngles();
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix(const float &aspectRatio);

        void setAsActiveCamera();
        bool isActive();
        static void unsetAsActiveCamera();
    
    private:
        glm::vec3 direction; // x, y, and z
        glm::vec3 horizontalDirection;
        glm::vec3 directionAngles; // yaw, pitch, and roll
        void updateDirectionVectors();
        void updateAxisVectors();
        glm::mat4 calculateViewMatrixToTarget(const glm::vec3 &target);
};

Camera* getActiveCamera();

#endif