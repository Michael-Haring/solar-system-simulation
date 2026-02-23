/*
   @file      main.cpp
   @author    Michael Haring
   @data      12/13/25

   This file contains non-class member functions, and main.
   This program is a simulation of our solar system.
 */

#include "simulation.hpp"
#include "space-object.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define GLFW_INIT_FAIL 2
#define GLAD_INIT_FAIL 3
#define GLFW_WINDOW_FAIL 4




struct InstanceData
{
	glm::mat4 model;
	glm::vec3 color;
	float pad;
};



/*
   Processes camera movement and rotation inputs from user
   @param     *window : current window
   &camera : camera being moved
deltaTime : change in time
 */
void processKeyboardInput(GLFWwindow *window, Camera &camera, float deltaTime);

/*
   callback method for resizing window. glfw handles the rest
   with their glfwPollEvents().
   @param     *window : not needed for me, required by glfw
width : width of window
height : height of window
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

/*
   Generates mesh for a sphere. Spheres will be very far away,
   so I am not using many triangles to try and save performance.
   @param     &vertices : amount of verticies
   &indices : amount of indices
sectorCount :
stackCount :
 */
void generateSphereMesh(vector<float> &vertices, vector<unsigned int> &indices,
		int sectorCount, int stackCount);




void processKeyboardInput(GLFWwindow *window, Camera &camera, float deltaTime)
{
	// Movement - WASD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processMovement(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processMovement(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processMovement(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processMovement(RIGHT, deltaTime);

	// Rotation - ARROW KEYS
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

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void generateSphereMesh(vector<float> &vertices, vector<unsigned int> &indices,
		int sectorCount = 36, int stackCount = 18)
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

int main()
{
	using std::cerr;
	// Window size and initialization
	const int WIDTH = 2560;
	const int HEIGHT = 1440;
	Camera camera(vec3(0.0f, 250.0f, 0.0f), vec3(0, 1, 0), -90.0f, -90.0f);
	Simulation solarSystem;

	//Space Object metric initialization
	//Masses
	float sunMass = 1.0e14f;
	float mercuryMass = 1.0e10f;
	float venusMass = 1.0e10f;
	float earthMass = 2.0e10f;
	float marsMass = 3.0e10f;
	float jupiterMass = 4.0e10f;
	float saturnMass = 3.2e10f;
	float uranusMass = 1.8e10f;
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
	vec3 initialMarsPos = vec3(50, 0, 0);
	vec3 initialJupiterPos = vec3(70, 0, 0);
	vec3 initialSaturnPos = vec3(90, 0, 0);
	vec3 initialUranusPos = vec3(120, 0, 0);
	vec3 initialNeptunePos = vec3(140, 0, 0);

	//Initial Velocity
	vec3 initialSunVel = vec3(0, 0, 0);
	vec3 initialMercuryVel = vec3(0, 0, 20);
	vec3 initialVenusVel = vec3(0, 0, 16);
	vec3 initialEarthVel = vec3(0, 0, 13.5);
	vec3 initialMarsVel = vec3(0, 0, 12);
	vec3 initialJupiterVel = vec3(0, 0, 10);
	vec3 initialSaturnVel = vec3(0, 0, 9);
	vec3 initialUranusVel = vec3(0, 0, 8);
	vec3 initialNeptuneVel = vec3(0, 0, 8);

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


	// Load glfw and glad. Create window
	if (!glfwInit())
	{
		cerr << "glfw unable to initialize\n";
		return GLFW_INIT_FAIL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Milky Way", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		cerr << "unable to create glfw window\n";
		return GLFW_WINDOW_FAIL;
	}

	glfwMakeContextCurrent(window);
	// V-Sync
	glfwSwapInterval(1);
	// window resizing callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "Failed to initialize GLAD \n";
		return GLAD_INIT_FAIL;
	}

	glEnable(GL_DEPTH_TEST);

	{
		// Shader work
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



		// Initialization of objects in solar system
		//Sun
		solarSystem.addObject(SpaceObject(sunMass, sunRadius, initialSunPos, initialSunVel, sunColor));
		// Mercury
		solarSystem.addObject(SpaceObject(mercuryMass, mercuryRadius, initialMercuryPos, initialMercuryVel, mercuryColor));
		// Venus
		solarSystem.addObject(SpaceObject(venusMass, venusRadius, initialVenusPos, initialVenusVel, venusColor));
		// Earth
		solarSystem.addObject(SpaceObject(earthMass, earthRadius, initialEarthPos, initialEarthVel, earthColor));
		// Mars
		solarSystem.addObject(SpaceObject(marsMass, marsRadius, initialMarsPos, initialMarsVel, marsColor));
		// Jupiter
		solarSystem.addObject(SpaceObject(jupiterMass, jupiterRadius, initialJupiterPos, initialJupiterVel, jupiterColor));
		// Saturn
		solarSystem.addObject(SpaceObject(saturnMass, saturnRadius, initialSaturnPos, initialSaturnVel, saturnColor));
		// Uranus
		solarSystem.addObject(SpaceObject(uranusMass, uranusRadius, initialUranusPos, initialUranusVel, uranusColor));
		// Neptune
		solarSystem.addObject(SpaceObject(neptuneMass, neptuneRadius, initialNeptunePos, initialNeptuneVel, neptuneColor));


		vector<InstanceData> instanceData;
		instanceData.reserve(solarSystem.getObjects().size());
		for (const auto &obj : solarSystem.getObjects())
		{
			InstanceData d;
			d.model = glm::translate(glm::mat4(1.0f), obj.getPosition());
			d.model = glm::scale(d.model, vec3(obj.getRadius()));
			d.color = obj.getColor();
			d.pad = 0.0f;
			instanceData.push_back(d);
		}

		unsigned int instanceVBO;
		glGenBuffers(1, &instanceVBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, instanceData.size() * sizeof(InstanceData), instanceData.data(), GL_DYNAMIC_DRAW);

		// mat4 occupies attribute locations 1..4
		for (int i = 0; i < 4; i++)
		{
			glEnableVertexAttribArray(1 + i);
			glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)(sizeof(glm::vec4) * i));
			glVertexAttribDivisor(1 + i, 1);
		}
		// color -> attrib 5
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void *)sizeof(glm::mat4));
		glVertexAttribDivisor(5, 1);
		glBindVertexArray(0);

		float dt = 0.01f;
		float lastFrame = 0.0f;
		//double fpsTime = 0.0;
		//int fpsFrames = 0;

		// main loop
		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			//code for framerate display
			/*
			   ++fpsFrames;
			   fpsTime += deltaTime;
			   if (fpsTime >= 0.5)
			   {
			   double fps = fpsFrames / fpsTime;
			   char title[128];
			   snprintf(title, sizeof(title), "Gravity Simulation - FPS: %.2f", fps);
			   glfwSetWindowTitle(window, title);
			   fpsFrames = 0;
			   fpsTime = 0.0;
			   }
			 */
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

			// update instanceData to match objects in solar system
			size_t objCount = solarSystem.getObjects().size();
			if (instanceData.size() != objCount)
				instanceData.resize(objCount);

			for (size_t i = 0; i < solarSystem.getObjects().size(); ++i)
			{
				instanceData[i].model = glm::translate(glm::mat4(1.0f), solarSystem.getObjects()[i].getPosition());
				instanceData[i].model = glm::scale(instanceData[i].model, vec3(solarSystem.getObjects()[i].getRadius()));
				instanceData[i].color = solarSystem.getObjects()[i].getColor();
			}

			glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
			GLsizeiptr bufSize = static_cast<GLsizeiptr>(instanceData.size() * sizeof(InstanceData));
			glBufferData(GL_ARRAY_BUFFER, bufSize, nullptr, GL_DYNAMIC_DRAW); // orphan previous storage
			glBufferSubData(GL_ARRAY_BUFFER, 0, bufSize, instanceData.data());
			glBindVertexArray(VAO);
			glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, (GLsizei)objCount);
			glBindVertexArray(0);

			glfwSwapBuffers(window);
		}

		// delete all buffers before glfwTerminate() - Love double deletes
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &instanceVBO);
	}
	glfwTerminate();
	return 0;
}
