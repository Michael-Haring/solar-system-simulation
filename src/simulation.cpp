/*
@file       simulation.cpp
@author     Michael Haring
@date       12/13/25

This file contains the implementation of the Simulation class, which manages
the collection of space objects and their interactions.
*/

#include "simulation.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

// SIMULATION CLASS PUBLIC IMPLEMENTATION

Simulation::Simulation(float g) : G(g) {}

void Simulation::addObject(const SpaceObject &obj)
{
    objects.push_back(obj);
}

void Simulation::step(float dt)
{
    const size_t N = objects.size();
    // const float eps = 1e-4f;
    if (N == 0)
        return;
    vector<vec3> forces(objects.size(), vec3(0.0f));
    vector<size_t> toRemove;
    vector<bool> removed(N, false);

    for (size_t i = 0; i < N; ++i)
    {
        if (removed[i])
            continue;
        for (size_t j = i + 1; j < N; ++j)
        {
            if (removed[j])
                continue;
            vec3 dir = objects[j].getPosition() - objects[i].getPosition();
            float dist = glm::length(dir);

            float minDist = objects[i].getRadius() + objects[j].getRadius();

            if (dist < minDist)
            {
                mergeObjects(i, j, toRemove);
                removed[j] = true;
                continue;
            }

            float distSqr = dist * dist;
            vec3 dirNorm = dist > 0.0f ? dir / dist : vec3(0.0f);
            vec3 force = G * objects[i].getMass() * objects[j].getMass() / distSqr * dirNorm;
            forces[i] += force;
            forces[j] -= force;
        }
    }
    if (!toRemove.empty())
    {
        vector<SpaceObject> newObjects;
        newObjects.reserve(objects.size());
        vector<vec3> newForces;
        newForces.reserve(forces.size());
        for (size_t idx = 0; idx < objects.size(); ++idx)
        {
            if (!removed[idx])
            {
                newObjects.push_back(std::move(objects[idx]));
                if (idx < forces.size())
                    newForces.push_back(forces[idx]);
                else
                    newForces.push_back(vec3(0.0));
            }
        }
        objects.swap(newObjects);
        forces.swap(newForces);
    }

    for (size_t i = 0; i < objects.size(); ++i)
    {
        objects[i].applyForce(forces[i], dt);
        objects[i].update(dt);
    }
}

void Simulation::mergeObjects(size_t i, size_t j, vector<size_t> &toRemove)
{
    const SpaceObject &obj1 = objects[i];
    const SpaceObject &obj2 = objects[j];
    float totalMass = obj1.getMass() + obj2.getMass();

    vec3 newVelocity = (obj1.getVelocity() * obj1.getMass() + obj2.getVelocity() *
                                                                  obj2.getMass()) /
                       totalMass;

    vec3 newPosition = (obj1.getPosition() * obj1.getMass() +
                        obj2.getPosition() * obj2.getMass()) /
                       totalMass;

    float newRadius = cbrtf(
        obj1.getRadius() * obj1.getRadius() * obj1.getRadius() +
        obj2.getRadius() * obj2.getRadius() * obj2.getRadius());

    vec3 newColor = (obj1.getMass() >= obj2.getMass()) ? obj1.getColor() : obj2.getColor();

    objects[i] = SpaceObject(totalMass, newRadius, newPosition, newVelocity, newColor);
    toRemove.push_back(j);
}

void Simulation::printPositions() const
{
    for (const auto &obj : objects)
    {
        vec3 pos = obj.getPosition();
        std::cout << "Object at (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    }
}

const vector<SpaceObject> &Simulation::getObjects() const { return objects; }