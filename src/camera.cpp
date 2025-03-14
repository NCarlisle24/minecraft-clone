#include <utils/camera.hpp>

Camera* Camera::activeCamera = NULL;
float Camera::horizontalMovementSpeed = DEFAULT_CAMERA_HORIZONTAL_MOVEMENT_SPEED;
float Camera::verticalMovementSpeed = DEFAULT_CAMERA_VERTICAL_MOVEMENT_SPEED;
float Camera::mouseSensitivity = DEFAULT_MOUSE_CAMERA_SENSITIVITY;
float Camera::fov = DEFAULT_DEGREE_FOV;
float Camera::nearPlane = DEFAULT_NEAR_PLANE;
float Camera::farPlane = DEFAULT_FAR_PLANE;

Camera* getActiveCamera() {
    return Camera::activeCamera;
}

Camera::Camera() {
    // (0, 0, 0) points in positive x direction
    directionAngles.x = 90.0f; // point in positive z direction by default
    directionAngles.y = 0.0f;
    directionAngles.z = 0.0f;

    updateDirectionVectors();
}

void Camera::updateDirectionVectors() {
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
        direction = glm::rotate(identityMat4, glm::radians(directionAngles.y), glm::cross(horizontalDirection, upVec3))
                    * glm::vec4(horizontalDirection, 1.0f);
    }

    updateAxisVectors();
}

void Camera::updateAxisVectors() {
    right = glm::cross(horizontalDirection, upVec3);
    left = -1.0f * right;

    up = glm::cross(right, horizontalDirection);
    down = -1.0f * up;
}

glm::mat4 Camera::calculateViewMatrixToTarget(const glm::vec3 &target) {
    glm::vec3 towardTargetZ = glm::normalize(position - target); // directly toward target
    glm::vec3 towardTargetX; // right/left when facing target (uses world up)
    
    if (abs(towardTargetZ.y) == 1.0f) { // if target is straight above or below
        towardTargetX = glm::cross(horizontalDirection, upVec3);
    } else {
        towardTargetX = glm::normalize(glm::cross(upVec3, towardTargetZ));
    }

    glm::vec3 towardTargetY = glm::cross(towardTargetZ, towardTargetX); // up/down when facing target

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = towardTargetX.x; // first row
    rotation[1][0] = towardTargetX.y;
    rotation[2][0] = towardTargetX.z;
    rotation[0][1] = towardTargetY.x; // second row
    rotation[1][1] = towardTargetY.y;
    rotation[2][1] = towardTargetY.z;
    rotation[0][2] = towardTargetZ.x; // third row
    rotation[1][2] = towardTargetZ.y;
    rotation[2][2] = towardTargetZ.z; 

    return rotation * translation;
}

glm::mat4 Camera::getProjectionMatrix(const float &aspectRatio) {
    return glm::perspective(glm::radians(DEFAULT_DEGREE_FOV), aspectRatio, DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);
}

glm::mat4 Camera::getViewMatrix() {
    return calculateViewMatrixToTarget(position + direction);
}

void Camera::setDirectionVector(const glm::vec3 &newDirection) {
    if (newDirection == zeroVec3) {
        std::cout << "Error: Zero vector passed as argument to Camera::setDirection()." << std::endl;
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
}

void Camera::setDirectionAngles(const glm::vec3 &newDirectionAngles, const bool &inRadians) {
    if (inRadians) {
        directionAngles.x = glm::degrees(newDirectionAngles.x);
        directionAngles.y = glm::degrees(newDirectionAngles.y);
        directionAngles.z = glm::degrees(newDirectionAngles.z);
    } else {
        directionAngles.x = newDirectionAngles.x;
        directionAngles.y = newDirectionAngles.y;
        directionAngles.z = newDirectionAngles.z;
    }

    directionAngles.x -= floor(directionAngles.x / 360) * 360.0f;

    updateDirectionVectors();
}

void Camera::rotateDirection(const glm::vec3 &deltaAngles, const bool &inRadians) {
    // convert angles and add
    if (inRadians) {
        directionAngles += glm::vec3(glm::degrees(deltaAngles.x), glm::degrees(deltaAngles.y), glm::degrees(deltaAngles.z));
    } else {
        directionAngles += glm::vec3(deltaAngles.x, deltaAngles.y, deltaAngles.z);
    }

    // clamp yaw
    directionAngles.x -= floor(directionAngles.x / 360) * 360.0f;

    updateDirectionVectors();
}

glm::vec3 Camera::getDirectionVector() {
    return direction;
}

glm::vec3 Camera::getHorizontalDirectionVector() {
    return horizontalDirection;
}

glm::vec3 Camera::getDirectionAngles() {
    return directionAngles;
}

void Camera::setAsActiveCamera() {
    activeCamera = this;
}

bool Camera::isActive() {
    return (activeCamera == this);
}

void Camera::unsetAsActiveCamera() {
    activeCamera = NULL;
}