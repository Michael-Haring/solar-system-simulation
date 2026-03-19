/*
* @file     instancedSphere_renderer.cpp
* @author   Michael Haring
* @data     3/18/26
*
* */

#include "instanced_sphere_renderer.hpp"
#include "shader.hpp"
#include "simulation.hpp"
#include "meshes.hpp"



InstancedSphereRenderer::InstancedSphereRenderer(const char* vertexPath, const char* fragmentPath)
    : m_shader(vertexPath, fragmentPath)
{
    setupMesh();
    setupInstanceAttributes();
}
InstancedSphereRenderer::~InstancedSphereRenderer()
{
    if (m_instanceVBO != 0)
        glDeleteBuffers(1, &m_instanceVBO);
    if (m_EBO != 0)
        glDeleteBuffers(1, &m_EBO);
    if (m_VBO != 0)
        glDeleteBuffers(1, &m_VBO);
    if (m_VAO != 0)
        glDeleteVertexArrays(1, &m_VAO);
}

void InstancedSphereRenderer::render(const Simulation& simulation, const Camera& camera, int width, int height)
{
    updateInstanceData(simulation);

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        1000.0f
    );

    glm::mat4 view = camera.getViewMatrix();

    m_shader.use();
    m_shader.setMat4("projection", projection);
    m_shader.setMat4("view", view);

    glBindVertexArray(m_VAO);
    glDrawElementsInstanced(GL_TRIANGLES,
                            static_cast<GLsizei>(m_indices.size()),
                            GL_UNSIGNED_INT,
                            0,
                            static_cast<GLsizei>(m_instanceData.size()));
    glBindVertexArray(0);
}

void InstancedSphereRenderer::setupMesh()
{
    generateSphereMesh(m_vertices, m_indices);
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenBuffers(1, &m_instanceVBO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(float),
                 m_vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(unsigned int),
                 m_indices.data(),
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glBindVertexArray(0);   
}

void InstancedSphereRenderer::setupInstanceAttributes()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    for (int i = 0; i < 4; ++i) {
        glEnableVertexAttribArray(1 + i);
        glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE,
                              sizeof(InstanceData),
                              (void*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(1 + i, 1);
    }
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 
                          sizeof(InstanceData),
                          (void*)sizeof(glm::mat4));
    glVertexAttribDivisor(5, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void InstancedSphereRenderer::updateInstanceData(const Simulation& simulation)
{
    const auto& objects = simulation.getObjects();

    m_instanceData.clear();
    m_instanceData.reserve(objects.size());

    for (const auto& object : objects)
    {
        InstanceData instance{};

        glm::mat4 model(1.0f);
        model = glm::translate(model, object.getPosition());
        model = glm::scale(model, glm::vec3(object.getRadius()));

        instance.model = model;
        instance.color = object.getColor();
        instance.pad = 0.0f;

        m_instanceData.push_back(instance);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
	GLsizeiptr bufSize = static_cast<GLsizeiptr>(m_instanceData.size() * sizeof(InstanceData));
	glBufferData(GL_ARRAY_BUFFER, bufSize, nullptr, GL_DYNAMIC_DRAW); // orphan previous storage
    glBufferSubData(GL_ARRAY_BUFFER, 0, bufSize, m_instanceData.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
