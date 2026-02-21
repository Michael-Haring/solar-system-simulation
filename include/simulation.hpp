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

    /*
    Constructor for Simulation object
    @param g : gravitational constant to use in simulation, default is 6.67430e-11f
    */
    Simulation(float g = 6.67430e-11f);

    /*
    Adds SpaceObject obj to objects<SpaceObject>
    @param obj : SpaceObject to add to simulation
    */
    void addObject(const SpaceObject &obj);

    /*
    Moves SpaceObject dynamically based on gravitational pull of other planets   
    @param dt : change in time since last step
    */
    void step(float dt);

    /*
    Used to merge SpaceObjects upon collision
    @param i : index of first object to merge
    @param j : index of second object to merge
    @param toRemove : vector of indices of objects to remove after merging, passed by reference
    */
    void mergeObjects(size_t i, size_t j, vector<size_t> &toRemove);

    /*
    prints position of planets
    Only used during initial tests, prior to graphical output   
    */
    void printPositions() const;
    /*
    Gets objects vector of SpaceObjects
    @return vector of SpaceObjects in Simulation
    */
    const vector<SpaceObject> &getObjects() const;

private:
    vector<SpaceObject> objects;
    float G;
};