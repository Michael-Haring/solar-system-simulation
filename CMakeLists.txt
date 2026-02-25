cmake_minimum_required(VERSION 3.10)

project(Simulation)

set(CMake_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB SOURCES 
	"src/*.cpp"
	"src/*.c"
)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})

add_executable(simulation ${SOURCES})

target_include_directories(simulation PRIVATE include)

target_compile_options(simulation PRIVATE 
	-g3
	-Wall
	-Wextra
	-Wunreachable-code
	-Wno-unused-parameter
	-Wredundant-decls
	-Wno-unused-variable
	-Wshadow
)

find_package(glfw3 REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(simulation 
	glfw
	OpenGL::GL
)
