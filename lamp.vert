#version 330 core
layout (location = 0) in vec3 a_position;
uniform mat4 a_view;
uniform mat4 a_model;
uniform mat4 a_projection;

void main()
{
    gl_Position = a_projection * a_view * a_model * vec4(a_position, 1.0f);
}
