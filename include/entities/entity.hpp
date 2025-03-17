#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <utils/helper.hpp>
#include <utils/camera.hpp>

class Entity {
    public:
        Camera* camera = NULL;

        Entity(Camera* const &camera = NULL);

        void setDirection(const glm::vec3 &newDirection);
        void setDirectionAngles(const glm::vec3 &newDirectionAngles, const AngleType &angleType = DEGREES);
        void rotateDirection(const glm::vec3 &deltaAngles, const AngleType &angleType = DEGREES);
        void move(const glm::vec3 &movementVector);
        void setPosition(const glm::vec3 &newPosition);

        glm::vec3 getDirection();
        glm::vec3 getHorizontalDirection();
        glm::vec3 getDirectionAngles();
        glm::vec3 getPosition();
        glm::vec3 getRightDirection();

    private: 
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 right = glm::vec3(-1.0f, 0.0f, 0.0f);
        glm::vec3 directionAngles = glm::vec3(90.0f, 0.0f, 0.0f);
        glm::vec3 horizontalDirection = glm::vec3(0.0f, 0.0f, 1.0f);

        void updateDirectionFromAngles(); // clamps yaw/pitch and sets direction
        void updateAxisVectors();
};


#endif