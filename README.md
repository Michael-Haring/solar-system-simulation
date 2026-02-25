## Solar System Simulation

A real-time 3d solar system simulation built in C++ using OpenGL. 
The project models gravitational forces between celestial bodies using dynamic gravitational force calculations based on the objects real position at runtime.
This allows for some very cool simulations, like a rouge star flying through our solar system.

## Disclaimer
Obviously, the distances must be shortened drastically to make it visually meaningful. This required fidgeting with the mass and velocity as well. 
I tried to keep object's metrics as realistic as possible.

## Dependencies
- g++
- OpenGL
- GLFW
- GLM (header-only)

## Install Dependencies (Ubuntu/Debian)
```bash
sudo apt install g++ libglfw3-dev libgl1-mesa-dev libglm-dev
```

## Build
From the project directory run:

```bash
make
```
```bash
build/simulation
```

## How it Works
The back end it fairly simple. This is an N-body calculation. Each body calcuating gravitational force on every other body. 
Then their new velocity is used to update their position. This loop can be sortened substancially by not calculating insignificant forces, which you could argue is everything except 
the Sun and perhaps Jupiter. I did not do this, as I do not have many bodies, and wanted to keep everything as realistic as possible.

## What I learned
This project is the first larger scale program I have created outside of school assignments, and also my first real graphics program.
I also switched from just using Vim, to using VSCode for this project. I thought it would be fitting for a larger project, with new libraries and APIs.
This is my first README, and really my first time considering other people who will be reading my code, other than someone who is grading it. I have used gitlab for a single class, 
and this is my first time really using github.

Further adaptations were made to increase build versatility. Originally, I was using Make, which worked for me. CMake is a more professional option that allows users with slightly different tools to generate a viable build system. This was my first time using CMake, and I thought it was a worthwhile addition considering its prevalence in the industry.


I have messed around with very small graphics programs, drawing shapes and moving them around. This project is the same thing, but introduces more dynamic movement and performance considerations.
This was the first graphics program where performance mattered at all to me. There were a couple attempts at optimizations made. The first was an instancing the sphere geometry, so
we could reduce our draw() calls to a single call, which I imagine would be slightly more useful with a larger amount of celestial bodies.

The second cool trick I learned was to orphan the previous storage. My implementation is updating the celestial bodies positions each frame dynamically based on the other bodies 
inflicting force. This can create a situation where your CPU stalls waiting for your GPU to be ready for the new positions. Orphaning allows you to tell the GPU to use those coordinates, 
then throw them away to get ready for the next set. This helps prevent the CPU getting stalled by the GPU messing around with data we are done with.
