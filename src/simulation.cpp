/*
@file       simulation.cpp
@author     Michael Haring
@date       12/13/25

This file contains the implementation of the Simulation class, which manages
the collection of space objects and their interactions.
*/

#include "simulation.hpp"
#include <iostream>
#include <cmath>

// SIMULATION CLASS PUBLIC IMPLEMENTATION

Simulation::Simulation(float g) : G(g) {}

void Simulation::buildStandardSS() 
{
//Stable to 6.9 million steps in current config

	//Masses
	float sunMass = 1.0e14f;
	float mercuryMass = 1.0e10f;
	float venusMass = 1.0e10f;
	float earthMass = 2.0e10f;
	float marsMass = 3.0e10f;
	float jupiterMass = 4.0e10f;
	float saturnMass = 3.2e10f;
	float uranusMass = 1.8e10f;    //1.8e10f
	float neptuneMass = 1.8e10f;

	//Radius
	float sunRadius = 3.0f;
	float mercuryRadius = 0.2f;
	float venusRadius = 0.55f;
	float earthRadius = 0.55f;
	float marsRadius = 0.35f;
	float jupiterRadius = 1.2f;
	float saturnRadius = 1.0f;
	float uranusRadius = 0.8f;
	float neptuneRadius = 0.8f;

	//Initial Position
	vec3 initialSunPos = vec3(0, 0, 0);
	vec3 initialMercuryPos = vec3(15, 0, 0);
	vec3 initialVenusPos = vec3(27, 0, 0);
	vec3 initialEarthPos = vec3(40, 0, 0);
	vec3 initialMarsPos = vec3(60, 0, 0);
	vec3 initialJupiterPos = vec3(90, 0, 0);
	vec3 initialSaturnPos = vec3(125, 0, 0);
	vec3 initialUranusPos = vec3(165, 0, 0);
	vec3 initialNeptunePos = vec3(220, 0, 0);

	//Initial Velocity
	vec3 initialSunVel = vec3(0, 0, 0);
	vec3 initialMercuryVel = vec3(0, 0, 20);
	vec3 initialVenusVel = vec3(0, 0, 16);
	vec3 initialEarthVel = vec3(0, 0, 13.5);
	vec3 initialMarsVel = vec3(0, 0, 11);
	vec3 initialJupiterVel = vec3(0, 0, 9.);
	vec3 initialSaturnVel = vec3(0, 0, 7.50);
	vec3 initialUranusVel = vec3(0, 0, 6.426);
	vec3 initialNeptuneVel = vec3(0, 0, 5.8);

	//Color
	vec3 sunColor = vec3(1, 0.85, 0.2);
	vec3 mercuryColor = vec3(1, 1, 1);
	vec3 venusColor = vec3(1, 0.65, 0);
	vec3 earthColor = vec3(0, 1, 0);
	vec3 marsColor = vec3(1, 0.15, 0);
	vec3 jupiterColor = vec3(1, 0.6, 0.2);
	vec3 saturnColor = vec3(0.9, 0.7, 0.2);
	vec3 uranusColor = vec3(0.3, 0.3, 1);
	vec3 neptuneColor = vec3(0, 0, 1);

    //Name
    string sunName = "Sun";
    string mercuryName = "Mercury";
    string venusName = "Venus";
    string earthName = "Earth";
    string marsName = "Mars";
    string jupiterName = "Jupiter";
    string saturnName = "Saturn";
    string uranusName = "Uranus";
    string neptuneName = "Neptune";

    // Initialization of objects in solar system
    //Sun
    addObject(SpaceObject(sunMass, sunRadius, initialSunPos, initialSunVel, sunColor, sunName));
    // Mercury
    addObject(SpaceObject(mercuryMass, mercuryRadius, initialMercuryPos, initialMercuryVel, mercuryColor, mercuryName));
    // Venus
    addObject(SpaceObject(venusMass, venusRadius, initialVenusPos, initialVenusVel, venusColor, venusName));
    // Earth
    addObject(SpaceObject(earthMass, earthRadius, initialEarthPos, initialEarthVel, earthColor, earthName));
    // Mars
    addObject(SpaceObject(marsMass, marsRadius, initialMarsPos, initialMarsVel, marsColor, marsName));
    // Jupiter
    addObject(SpaceObject(jupiterMass, jupiterRadius, initialJupiterPos, initialJupiterVel, jupiterColor, jupiterName));
    // Saturn
    addObject(SpaceObject(saturnMass, saturnRadius, initialSaturnPos, initialSaturnVel, saturnColor, saturnName));
    // Uranus
    addObject(SpaceObject(uranusMass, uranusRadius, initialUranusPos, initialUranusVel, uranusColor, uranusName));
    // Neptune
    addObject(SpaceObject(neptuneMass, neptuneRadius, initialNeptunePos, initialNeptuneVel, neptuneColor, neptuneName));
    std::cerr << mercuryName << "'s initial position is: " << initialMercuryPos.x << "\n";
    std::cerr << venusName << "'s initial position is: " << initialVenusPos.x << "\n";
    std::cerr << earthName << "'s initial position is: " << initialEarthPos.x << "\n";
    std::cerr << marsName << "'s initial position is: " << initialMarsPos.x << "\n";
    std::cerr << jupiterName << "'s initial position is: " << initialJupiterPos.x << "\n";
    std::cerr << saturnName << "'s initial position is: " << initialSaturnPos.x << "\n";
    std::cerr << uranusName << "'s initial position is: " << initialUranusPos.x << "\n";
    std::cerr << neptuneName << "'s initial position is: " << initialNeptunePos.x << "\n\n";
}




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
    string newName = (obj1.getMass() >= obj2.getMass()) ? obj1.getName() : obj2.getName();

    objects[i] = SpaceObject(totalMass, newRadius, newPosition, newVelocity, newColor, newName);
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
