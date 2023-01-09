#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

void main()
{
    vec3 normal = (normalize(Normal) + 1.0f) * 0.5f;
    FragColor = vec4(normal, 1.0);
}