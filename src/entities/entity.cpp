#include <entities/entity.hpp>

Entity::Entity(Camera* const &camera) {
    this->camera = camera;
    if (camera != NULL) {
        camera->setDirectionDirect(direction, horizontalDirection, directionAngles);
        camera->setPosition(position);
    }
}

void Entity::updateDirectionFromAngles() {
    directionAngles.x -= floor(directionAngles.x / 360) * 360.0f;

    if (directionAngles.x == 90.0f) { // positive z
        horizontalDirection.x = 0.0f;
        horizontalDirection.z = 1.0f;
    } else if (directionAngles.x == -90.0f) { // negative z
        horizontalDirection.x = 0.0f;
        horizontalDirection.z = -1.0f;
    } else if (directionAngles.x == 0.0f){ // positive x
        horizontalDirection.x = 1.0f;
        horizontalDirection.z = 0.0f;
    } else if (directionAngles.x == 180.0f) { // negative x
        horizontalDirection.x = -1.0f;
        horizontalDirection.z = 0.0f;
    } else {
        horizontalDirection.x = cos(glm::radians(directionAngles.x));
        horizontalDirection.z = sin(glm::radians(directionAngles.x));
    }

    if (directionAngles.y >= 90.0f) {
            directionAngles.y = 90.0f;
            direction = upVec3;
    } else if (directionAngles.y <= -90.0f) {
            directionAngles.y = -90.0f;
            direction = downVec3;
    } else { // rotate horizontal vector up by directionAngles.y
        // TODO: simplify this function (camera too)
        direction = glm::rotate(identityMat4, glm::radians(directionAngles.y), glm::cross(horizontalDirection, upVec3))
                    * glm::vec4(horizontalDirection, 1.0f);
    }

    updateAxisVectors();
}

void Entity::updateAxisVectors() {
    right = glm::cross(horizontalDirection, upVec3);
}


void Entity::setDirection(const glm::vec3 &newDirection) {
    if (newDirection == zeroVec3) {
        std::cerr << "Error: Zero vector passed as argument to Entity::setDirection()." << std::endl;
        return;
    }

    direction = glm::normalize(newDirection);

    if (!(newDirection.x == 0.0f && newDirection.z == 0.0f)) {
        horizontalDirection.x = newDirection.x;
        horizontalDirection.z = newDirection.z;
        horizontalDirection = glm::normalize(horizontalDirection);

        directionAngles.x = glm::degrees(atan2(direction.x, direction.y));
    }

    directionAngles.y = glm::degrees(asin(direction.y));
    // keep roll the same

    direction = newDirection;

    updateAxisVectors();
    if (camera != NULL) {
        camera->setDirectionDirect(direction, horizontalDirection, directionAngles);
    }
}

void Entity::setDirectionAngles(const glm::vec3 &newDirectionAngles, const AngleType &angleType) {
    if (angleType == RADIANS) {
        directionAngles.x = glm::degrees(newDirectionAngles.x);
        directionAngles.y = glm::degrees(newDirectionAngles.y);
        directionAngles.z = glm::degrees(newDirectionAngles.z);
    } else {
        directionAngles = newDirectionAngles;
    }

    updateDirectionFromAngles();

    if (camera != NULL) {
        camera->setDirectionDirect(direction, horizontalDirection, directionAngles);
    }
}

void Entity::rotateDirection(const glm::vec3 &deltaAngles, const AngleType &angleType) {
    // convert angles and add
    if (angleType == RADIANS) {
        directionAngles += glm::vec3(glm::degrees(deltaAngles.x), glm::degrees(deltaAngles.y), glm::degrees(deltaAngles.z));
    } else {
        directionAngles += deltaAngles;
    }

    updateDirectionFromAngles();
    if (camera != NULL) {
        camera->setDirectionDirect(direction, horizontalDirection, directionAngles);
    }
}

void Entity::move(const glm::vec3 &movementVector) {
    position += movementVector;
    if (camera != NULL) {
        camera->setPosition(position);
    }
}

void Entity::setPosition(const glm::vec3 &newPosition) {
    position = newPosition;
    if (camera != NULL) {
        camera->setPosition(position);
    }
}

glm::vec3 Entity::getDirection() {
    return direction;
}

glm::vec3 Entity::getHorizontalDirection() {
    return horizontalDirection;
}

glm::vec3 Entity::getDirectionAngles() {
    return directionAngles;
}

glm::vec3 Entity::getPosition() {
    return position;
}

glm::vec3 Entity::getRightDirection() {
    return right;
}