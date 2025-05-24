#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <mcc-utils/helper.hpp>
#include <mcc-utils/entities/entity.hpp>

#define DEFAULT_PLAYER_HORIZONTAL_MOVEMENT_SPEED 5.0f
#define DEFAULT_PLAYER_VERTICAL_MOVEMENT_SPEED 5.0f
#define DEFAULT_MOUSE_CAMERA_SENSITIVITY 0.1f

class Player : public Entity {
    public:
        using Entity::Entity;

        static float mouseCameraSensitivity;
        float horizontalMovementSpeed = DEFAULT_PLAYER_HORIZONTAL_MOVEMENT_SPEED;
        float verticalMovementSpeed = DEFAULT_PLAYER_VERTICAL_MOVEMENT_SPEED;
};

#endif