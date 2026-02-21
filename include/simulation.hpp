/*
@file       simulation.hpp
@author     Michael Haring
@date       12/13/25

This file contains the declaration of the Simulation class, which manages
the collection of space objects and their interactions.
*/

#pragma once
#include "space-object.hpp"
#include <vector>
using std::vector;

class Simulation
{
public:
    Simulation(float g = 6.67430e-11f);
    void addObject(const SpaceObject &obj);
    void step(float dt);
    void mergeObjects(size_t i, size_t j, vector<size_t> &toRemove);
    void printPositions() const;
    const vector<SpaceObject> &getObjects() const;

private:
    vector<SpaceObject> objects;
    float G;
};