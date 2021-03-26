#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;
layout (std140) uniform Matrices
{
    mat4 a_projection;
    mat4 a_view;
};
out vec2 TexCoords;
void main(void)
{
    TexCoords = aTexCoords;
    gl_Position = a_projection * a_view * aInstanceMatrix * vec4(aPos,1.0f);
}
