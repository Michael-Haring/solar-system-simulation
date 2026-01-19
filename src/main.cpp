/*
 @file      main.cpp
 @author    Michael Haring
 @data      12/13/25

 This file contains non-class member functions, and main.
 This program is a simulation of our solar system.

 I am very new to graphics, and thes libraries, so bare with inefficiencies.
 Overall so far I am rather proud of how well this works.

 Currently I am very far from the objects, this is not good for efficiency.(really). 
 It is a matter of proportions and having everything look nice. 
 I think I could have made the objects rediculously small, maybe similar or even 
 worse performance issues. Look into this.

 Currently objects and color instanced seperately.
 Try instancing them together.

 (BUG) Also currently when objects merge the insanced colors begin shifting.
 Changing the color of each planet. 
 */

#include "simulation.hpp"
#include "space-object.hpp"
#include "shader.h"
#include "camera.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>



/*
 Processes camera movement and rotation inputs from user
 @param     *window : current window
            &camera : camera being moved
            deltaTime : change in time
*/
void processKeyboardInput(GLFWwindow* window, Camera& camera, float deltaTime) {
    //Movement - WASD
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processMovement(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processMovement(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processMovement(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processMovement(RIGHT, deltaTime);

    //Rotation - ARROW KEYS
    float xDir = 0.0f, yDir = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        xDir = -1.0f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        xDir = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        yDir = -1.0f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        yDir = 1.0f;
    
    if (xDir != 0.0f || yDir != 0.0f)
        camera.processRotation(xDir, yDir, deltaTime);
        
}

/*
 callback method for resizing window. glfw handles the rest 
 with their glfwPollEvents().
 @param     *window : not needed for me, required by glfw
            width : width of window
            height : height of window
*/
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

/*
 Generates mesh for a sphere. Spheres will be very far away,
 so I am not using many triangles to try and save performance.
 @param     &vertices : amount of verticies
            &indices : amount of indices
            sectorCount : 
            stackCount : 
*/
void generateSphereMesh(vector<float> &vertices, vector<unsigned int> &indices,
                        int sectorCount = 128, int stackCount = 64)
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
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

int main()
{
    using std::cerr;    using std::cout;
    //Window size and initialization
    const int WIDTH = 2560;     const int HEIGHT = 1440;
    Camera camera(vec3(0.0f, 200.0f, 0.0f), vec3(0, 1, 0), -90.0f, -90.0f);
    Simulation solarSystem;

    //Load glfw and glad. Create window
    if (!glfwInit())
    {
        cerr << "glfw unable to initialize\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Gravity Simulation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        cerr << "unable to create glfw window\n";
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cerr << "Failed to initialize GLAD \n";
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);

    {
        //Shader work
        Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

        vector<float> vertices;
        vector<unsigned int> indices;
        generateSphereMesh(vertices, indices);

        unsigned int VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        //Initialization of objects in solar system
                                //      mass-----radiuas--position--------velocity-----color
        //Sun                   14
        solarSystem.addObject(SpaceObject(1.0e14f, 3.0f, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 0.85, 0.2)));

        //Mercury
        solarSystem.addObject(SpaceObject(1.0e10f, 0.2f, vec3(15, 0, 0), vec3(0, 0, 20), vec3(1, 1, 1)));
        //Venus
        solarSystem.addObject(SpaceObject(1.0e10f, 0.55f, vec3(27, 0, 0), vec3(0, 0, 16), vec3(1, 0.65, 0)));
        //Earth
        solarSystem.addObject(SpaceObject(2.0e10f, 0.55f, vec3(40, 0, 0), vec3(0, 0, 13.5), vec3(0, 1, 0)));
        //Mars
        solarSystem.addObject(SpaceObject(3.0e10f, 0.35f, vec3(50, 0, 0), vec3(0, 0, 12), vec3(1, 0.15, 0)));//prefect
        //Jupiter
        solarSystem.addObject(SpaceObject(4.0e10f, 1.2f, vec3(70, 0, 0), vec3(0, 0, 10), vec3(1, 0.6, 0.2)));//prefect
        //Saturn
        solarSystem.addObject(SpaceObject(3.2e10f, 1.0f, vec3(90, 0, 0), vec3(0, 0, 9), vec3(0.9f, 0.7f, 0.2)));//prefect
        //Uranus....lol 8
        solarSystem.addObject(SpaceObject(1.8e10f, 0.8f, vec3(120, 0, 0), vec3(0, 0, 8), vec3(0.3, 0.3, 1)));//prefect
        //Neptune
        solarSystem.addObject(SpaceObject(1.8e10f, 0.8f, vec3(140, 0, 0), vec3(0, 0, 8), vec3(0, 0, 1)));//prefect



        //instanced objects
        vector<glm::mat4> modelMatrices;
        modelMatrices.reserve(solarSystem.getObjects().size());
        for (const auto& obj : solarSystem.getObjects()) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), obj.getPosition());
            model = glm::scale(model, vec3(obj.getRadius()));
            modelMatrices.push_back(model);
        }
        unsigned int instanceVBO;
        glGenBuffers(1, &instanceVBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data(), GL_DYNAMIC_DRAW);

        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(1 + i);
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
            glVertexAttribDivisor(1 + i, 1);
        }

        //INSTANCE COLOR
        vector<glm::vec3> instanceColors;
        for (const auto& obj : solarSystem.getObjects())
            instanceColors.push_back(obj.getColor());

        unsigned int colorVBO;
        glGenBuffers(1, &colorVBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, instanceColors.size() * sizeof(vec3), instanceColors.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
        glVertexAttribDivisor(5, 1);

        glBindVertexArray(0);

        float dt = 0.01f;
        float lastFrame = 0.0f;
        //main loop
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glfwPollEvents();
            processKeyboardInput(window, camera, deltaTime);
            solarSystem.step(dt);

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 1000.0f);
            shader.setMat4("view", camera.getViewMatrix());
            shader.setMat4("projection", projection);
            shader.setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));

            for (size_t i = 0; i < solarSystem.getObjects().size(); ++i)
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), solarSystem.getObjects()[i].getPosition());
                model = glm::scale(model, vec3(solarSystem.getObjects()[i].getRadius()));
                modelMatrices[i] = model;
            }
            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data());

            glBindVertexArray(VAO);
            glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, solarSystem.getObjects().size());
            glBindVertexArray(0);

            glfwSwapBuffers(window);
        }
        //delete all buffers before glfwTerminate()
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &instanceVBO);
    }
    glfwTerminate();
    return 0;
}