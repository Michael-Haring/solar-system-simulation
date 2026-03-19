/*
* @file     meshes.cpp
* @author   Michael Haring
* @date     3/18/26
* */

#include <cmath>
#include "meshes.hpp"

void generateSphereMesh(vector<float> &vertices, vector<unsigned int> &indices,
		int sectorCount, int stackCount)
{
	vertices.clear();
	indices.clear();
	const float PI = 3.141592653592f;

	for (int i = 0; i <= stackCount; ++i)
	{
		float stackAngle = PI / 2 - i * PI / stackCount;
		float xy = cos(stackAngle);
		float z = sin(stackAngle);
		for (int j = 0; j <= sectorCount; ++j)
		{
			float sectorAngle = j * 2 * PI / sectorCount;
			float x = xy * cos(sectorAngle);
			float y = xy * sin(sectorAngle);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}

	for (int i = 0; i < stackCount; ++i)
	{
		int k1 = i * (sectorCount + 1);
		int k2 = k1 + sectorCount + 1;
		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != stackCount - 1)
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}
