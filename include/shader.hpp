/*
 @file      shader.h
 @author    Michael Haring
 @date      12/13/25

This file contains the declaration of the Shader class, which loads,
compiles, and links vertex and fragment shaders.
 */

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
using std::string;

class Shader {
    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        void use() const;
        void checkCompileErrors(unsigned int shader, const string &type);

        void setMat4(const string &name, const glm::mat4 &mat) const;
        void setVec3(const string &name, const glm::vec3 &vec) const;

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
};