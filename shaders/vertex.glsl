#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 iRow0;
layout(location = 2) in vec4 iRow1;
layout(location = 3) in vec4 iRow2;
layout(location = 4) in vec4 iRow3;
layout(location = 5) in vec3 instanceColor;
out vec3 FragColor;

uniform mat4 view;
uniform mat4 projection;

void main() {
    mat4 instanceModel = mat4(iRow0, iRow1, iRow2, iRow3);
    gl_Position = projection * view * instanceModel * vec4(aPos, 1.0);
    FragColor = instanceColor;
}