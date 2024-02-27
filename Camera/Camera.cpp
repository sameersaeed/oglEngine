#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

// for moving around
void Camera::processKeyboard(Directions direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    switch (direction)
    {
        case UP:
            Position += Up * velocity;
            break;
        case DOWN:
            Position -= Up * velocity;
            break;
        case FORWARD:
            Position += Front * velocity;
            break;
        case BACKWARD:
            Position -= Front * velocity;
            break;
        case LEFT:
            Position -= Right * velocity;
            break;
        case RIGHT:
            Position += Right * velocity;
            break;
        case ROTATE_LEFT:
            Yaw -= velocity * 25;
            updateVectors();
            break;
        case ROTATE_RIGHT:
            Yaw += velocity * 25;
            updateVectors();
            break;
    }
}

// for looking around
void Camera::processMouse(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateVectors();
}

// for zooming
void Camera::processScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
