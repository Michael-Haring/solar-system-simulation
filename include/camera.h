/*
@file       camera.h
@author     Michael Haring
@date       12/12/25
*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
    
    public:
        Camera(vec3 _pos, vec3 _up, float _yaw, float _pitch);
        glm::mat4 getViewMatrix() const;
        void processMovement(Camera_Movement direction, float deltaTime);
        void processRotation(float xoffset, float yoffset, float deltaTime);
        vec3 getPosition() const;
        vec3 getFront() const;
    private:
    void updateCameraVectors();
    
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;
    float yaw;
    float pitch;
    const float MOV_SPEED = 10.0f;
    const float ROT_SPEED = 90.0f;
};