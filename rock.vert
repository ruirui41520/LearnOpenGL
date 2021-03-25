#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;
out VS_OUT {
    vec2 texCoords;
} vs_out;
uniform mat4 a_view;
uniform mat4 a_projection;

void main(void)
{
    vs_out.texCoords = aTexCoords;
    gl_Position = a_projection * a_view * aInstanceMatrix *vec4(aPos,1.0f);
}
