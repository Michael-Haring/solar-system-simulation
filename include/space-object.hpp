/*
 @file      space-object.hpp
 @author    Michael Haring
 @data      11/27/25
 @version   0.1

 C++ header file for SpaceObject.
 These will be the only objects in the simulation.
 I considered making a virtual hierarchy to distinguish
*/
#pragma once
#include <glm/glm.hpp>

using glm::vec3;

class SpaceObject {
    
    public:
        SpaceObject(const float m, const float r, 
            const vec3& pos, const vec3& vel, const vec3& col);

        ~SpaceObject() = default;
        void update(float dt);
        void applyForce(const vec3& force, float dt);

        float getMass() const;
        float getRadius() const;
        vec3 getPosition() const;
        vec3 getVelocity() const;
        vec3 getColor() const;

        void setVelocity(const vec3& v);


    private:
        float mass;
        float radius;
        vec3 position;
        vec3 velocity;
        vec3 color;

};