#version 330 core
layout (location = 0) in vec3 a_vertex;
uniform mat4 a_projection;
uniform mat4 a_view;
uniform mat4 a_model;

void main()
{
    gl_Position = a_projection * a_view * a_model * vec4(a_vertex, 1.0f);
}
