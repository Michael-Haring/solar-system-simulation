/*
*/

#pragma once
#include "space-object.hpp"
#include <vector>
using std::vector;

class Simulation {
    public:
        Simulation(float g = 6.67430e-11f);
        void addObject(const SpaceObject& obj);
        void step(float dt);
        void mergeObjects(size_t i, size_t j, vector<size_t>& toRemove);
        void printPositions() const;
        const vector<SpaceObject>& getObjects() const;

        private:
            vector<SpaceObject> objects;
            float G;
};