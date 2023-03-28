#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 worldPosition;

out vec3 ourColor;
void main()
{
    vec3 newPos = normalize(worldPosition);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    ourColor = vec3(
    worldPosition[0]/30,
    worldPosition[1]/10,
    worldPosition[2]/10);
}   