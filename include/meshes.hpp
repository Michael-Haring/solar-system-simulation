/*
* @file     meshes.hpp
* @author   Michael Haring
* @date     3/17/26
*
* Moved here to clean up main.cpp.
* I only have a single mesh currently, all objects are spheres in my solar system.
* */

#pragma once
#include <vector>

using std::vector;


/*
   Generates mesh for a sphere. Spheres will be very far away,
   so I am not using many triangles to try and save performance.
   @param       &vertices:      amount of verticies
                &indices:       amount of indices
                sectorCount:    use default values
                stackCount:     use default values
 */
void generateSphereMesh(vector<float> &vertices, vector<unsigned int> &indices,
                        int sectorCount = 36, int stackCount = 18);


