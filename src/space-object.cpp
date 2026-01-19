/*

*/

#include "space-object.hpp"

// PUBLIC IMPLEMENTATION FOR SPACEOBJECT CLASS

SpaceObject::SpaceObject(const float m, const float r,
                         const vec3& pos, const vec3& vel, const vec3& col)
    : mass(m), radius(r), position(pos), velocity(vel), color(col) {}




void SpaceObject::update(float dt)
{
    position += velocity * dt;
}

void SpaceObject::applyForce(const vec3 &force, float dt)
{   
    if (mass <= 0) return;
    vec3 acceleration = force / mass;
    velocity += acceleration * dt;
}

float SpaceObject::getMass() const
{
    return mass;
}

float SpaceObject::getRadius() const
{
    return radius;
}

vec3 SpaceObject::getPosition() const
{
    return position;
}

vec3 SpaceObject::getVelocity() const
{
    return velocity;
}

vec3 SpaceObject::getColor() const
{
    return color;
}


void SpaceObject::setVelocity(const vec3& v) {
    velocity = v;
}
