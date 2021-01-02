#version 330 core
uniform vec3 lampColor;
uniform vec3 objColor;
out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(lampColor * objColor, 1.0f);
}
