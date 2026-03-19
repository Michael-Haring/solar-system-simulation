/*
* @file     instanced_sphere_renderer.hpp
* @author   Michael Haring
* @date     3/17/26
*
* Class that manages my Sphere rendering
* Manages instanced geometry and renders meshes.
*
* */

#pragma once
#include "simulation.hpp"
#include "camera.hpp"
#include "shader.hpp"

class InstancedSphereRenderer
{
public:
    /*
    *   Contructor for renderer
    *   @param      vertexPath:     path for vertex shader file
    *               fragmentPath:   path for fragment shader file
    * */
    InstancedSphereRenderer(const char* vertexPath, const char* fragmentPath);

    /*
    *   Destructor for the renderer object
    * */
    ~InstancedSphereRenderer();

    /*
    *   renders meshes to screen, does transformations for view and 3d space. Also updates Instance data
    *   @param      simulation:     simulation object to render (solarSystem)
    *               camera:         user's camera
    *               width:          width of screen
    *               height:         height of screen
    * */
    void render(const Simulation& simulation, const Camera& camera, int width, int height);


private:
    /*
    *   Struct of instanced data.
    *   Model for transforms and scales, each having its own color
    *   color will be replaced with textureArrayID in next refactor
    * */
    struct InstanceData
    {
        glm::mat4 model;
        glm::vec3 color;
        float pad;
    };

    /*
    * sets up mesh for the constructor
    * */
    void setupMesh();

    /*
    *   sets up InstanceData with shader file attributes
    * */
    void setupInstanceAttributes();

    /*
    *   updates InstanceData 
    *   @param      simulation: scene to update with, (solarSystem)
    * */
    void updateInstanceData(const Simulation& simulation);


    Shader m_shader;
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_EBO = 0;
    unsigned int m_instanceVBO = 0;

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<InstanceData> m_instanceData;

};
