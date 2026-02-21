/*
@file       camera.cpp
@author     Michael Haring
@date       12/13/25

This file contains the implementation of the Camera class, which handles
the camera's position, orientation, and movement.
*/

#include "camera.hpp"

Camera::Camera(vec3 _pos,vec3 _up, float _yaw, float _pitch)
    : position(_pos), worldUp(_up), yaw(_yaw), pitch(_pitch) {
        updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}
void Camera::processMovement(Camera_Movement direction, float deltaTime) {
    float velocity = MOV_SPEED * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
    
}
void Camera::processRotation(float xoffset, float yoffset, float deltaTime) {
    
    yaw += xoffset * ROT_SPEED * deltaTime;
    pitch += yoffset * ROT_SPEED * deltaTime;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

vec3 Camera::getPosition() const {
    return position;
}

vec3 Camera::getFront() const {
    return front;
}


//PRIVATE--------

void Camera::updateCameraVectors() {
    vec3 tempFront;
    tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tempFront.y = sin(glm::radians(pitch));
    tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(tempFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
