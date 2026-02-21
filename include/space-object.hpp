/*
 @file      space-object.hpp
 @author    Michael Haring
 @data      11/27/25
 @version   0.1

This file contains the declaration of the SpaceObject class, which represents
a celestial body in the simulation.
*/

#pragma once
#include <glm/glm.hpp>

using glm::vec3;

/*

*/
class SpaceObject
{

public:
    /*
    SpaceObject constructor
    @param m : mass of object
    @param r : radius of object
    @param pos : initial position of object in space
    @param vel : initial velocity of object in space
    @param col : color of object for rendering
    */
    SpaceObject(const float m, const float r,
                const vec3 &pos, const vec3 &vel, const vec3 &col);

    /*
    SpaceObject destructor
    */
    ~SpaceObject() = default;

    /*
    updates SpaceObjects fields position adn velocity
    @param dt - time change since last calculation
    */
    void update(float dt);

    /*
    applies gravitational force onto another object
    @param force : 3d vector of force to apply to object
    @param dt : time change since last calculation
    */
    void applyForce(const vec3 &force, float dt);

    /*
    Gets SpaceObjects mass
    @return this->mass
    */
    float getMass() const;

    /*
    Gets SpaceObjects radius
    @return this->radius
    */
    float getRadius() const;

    /*
    Gets SpaceObjects position
    @return this->position
    */
    vec3 getPosition() const;

    /*
    Gets SpaceObjects velocity
    @return this->velocity
    */
    vec3 getVelocity() const;

    /*
    Gets SpaceObjects color
    @return this->color
    */
    vec3 getColor() const;

    /*
    Sets SpaceObjects velocity, used for defining initial velocity
    @param 3d vector of velocities
    */
    void setVelocity(const vec3 &v);

private:
    float mass;
    float radius;
    vec3 position;
    vec3 velocity;
    vec3 color;
};