/*
@file       camera.h
@author     Michael Haring
@date       12/12/25

This file contains the declaration of the Camera class, which handles
the camera's position, orientation, and movement.
*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;

    /*
    
    */
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

/*
Camera class creates a camera obj in which the simulation si viewed from
Minimal implementation

WASD to move camera
Arrow keys to rotate camera
*/
class Camera
{

public:
    /*
    Contructor for Camera object.
    @param _pos The initial position of the camera in world space.
    @param _up The world up vector, typically (0, 1, 0).
    @param _yaw The initial yaw angle (rotation around the Y axis) in degrees.
    @param _pitch The initial pitch angle (rotation around the X axis) in degrees.
    */
    Camera(vec3 _pos, vec3 _up, float _yaw, float _pitch);

    /*
    Returns the view matrix for the camera.
    @return The view matrix.
    */
    glm::mat4 getViewMatrix() const;

    /*
    Processes input for camera movement.
    @param direction The direction of movement (FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN).
    @param deltaTime The time elapsed since the last frame   
    */
    void processMovement(Camera_Movement direction, float deltaTime);

    /*
    processes input for camera rotation.
    @param xoffset The offset in the x direction (yaw).
    @param yoffset The offset in the y direction (pitch).
    @param deltaTime The time elapsed since the last frame.
    */
    void processRotation(float xoffset, float yoffset, float deltaTime);

    /*
    Returns the position of the camera.
    @return The position of the camera.
    */
    vec3 getPosition() const;

    /*
    Returns the front vector of the camera, which indicates the direction the camera is facing.
    @return The front vector of the camera.
    */
    vec3 getFront() const;

private:
    /*
    Updates camera vectors
    */
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