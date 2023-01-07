#version 330 core
out vec4 FragColor;

in vec3 Normal;

void main()
{
    vec3 normal = (normalize(Normal) + 1.0f) * 0.5f;
    FragColor = vec4(normal, 1.0);
}