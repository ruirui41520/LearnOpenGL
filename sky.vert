#version 330 core
layout(location = 0) in vec3 aPos;
layout (std140) uniform Matrices
{
    mat4 a_projection;
    mat4 a_view;
};

out VS_OUT
{
    vec3 TexCoords;
} vs_out;

void main(void)
{
    vs_out.TexCoords = aPos;
    vec4 pos = a_projection * a_view * vec4(aPos,1.0);
    gl_Position = pos.xyww;
}
