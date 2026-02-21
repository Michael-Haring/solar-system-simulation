/*
 @file      shader.h
 @author    Michael Haring
 @date      12/13/25

This file contains the declaration of the Shader class, which loads,
compiles, and links vertex and fragment shaders.

set v3 and m4 function headers??

 */

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
using std::string;

class Shader
{
public:
    /*
    Shader object contructor

    */
    Shader(const char *vertexPath, const char *fragmentPath);

    /*
    Shader object destructor   
    */
    ~Shader();

    /*
    simply calls glUseProgram(Shader.ID) to use the shader program
     */
    void use() const;

    /*
    Checks for shader compilation and program linking errors and prints them to stderr
    @param shader : shader or program ID to check
    @param type : type of shader ("VERTEX", "FRAGMENT")
    */
    void checkCompileErrors(unsigned int shader, const string &type);

    /*
    Sets 4d matrix for shaders  - used to set   camera view matrix and projection matrix
    @param name : name of uniform variable in shader
    @param mat : matrix to set uniform variable to
    */
    void setMat4(const string &name, const glm::mat4 &mat) const;

    /*
    Sets 3d vector for spaceobject colors
    @param name : name of uniform variable in shader
    @param vec : vector to set uniform variable to
    */
    void setVec3(const string &name, const glm::vec3 &vec) const;

    /*
    Copy constructor for Shader object
    */
    Shader(const Shader &) = delete;

    /*
    assignment operator for shader object
    */
    Shader &operator=(const Shader &) = delete;

    unsigned int ID;
};