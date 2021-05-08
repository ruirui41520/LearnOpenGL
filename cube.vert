#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (std140) uniform Matrices
{
    mat4 aView;
    mat4 aProjection;
};

out vec2 TexCoords;

uniform mat4 a_model;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = aProjection * aView * a_model * vec4(aPos, 1.0);
}
