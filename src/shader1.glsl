#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 auv;

out vec2 uv;

uniform mat4 trans;

void main()
{
    gl_Position = trans * vec4(aPos, 1.0f);
    uv = vec2(auv.x, 1.0 - auv.y);
}