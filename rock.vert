#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;
out vec2 TexCoords;
uniform mat4 a_view;
uniform mat4 a_projection;

void main(void)
{
    TexCoords = aTexCoords;
    gl_Position = a_projection * a_view * aInstanceMatrix * vec4(aPos,1.0f);
}
