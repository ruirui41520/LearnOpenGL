#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 texCoords;
} vs_out;

uniform mat4 a_model;
uniform mat4 a_view;
uniform mat4 a_projection;

void main()
{
    vs_out.texCoords = aTexCoords;
    gl_Position = a_projection * a_view * a_model * vec4(aPos, 1.0);
}
