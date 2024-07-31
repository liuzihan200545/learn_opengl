#version 330 core
in vec2 uv;

out vec4 FragColor;

uniform sampler2D Sampler1;

void main()
{
    vec4 texture1 = texture(Sampler1,uv);
    FragColor = texture1;
}