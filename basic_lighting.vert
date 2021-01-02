#version 330 core
layout(location = 0)in vec3 qt_vertex;
layout(location = 1)in vec3 qt_normal;
uniform mat4 a_model;
uniform mat4 a_view;
uniform mat4 a_projection;

out vec3 fragPos;
out vec3 normal;

void main(void)
{
    fragPos = vec3(a_model * vec4(qt_vertex,1.0f));
    normal = mat3(transpose(inverse(a_model))) * qt_normal;
    gl_Position = a_projection * a_view * vec4(fragPos,1.0);

}
