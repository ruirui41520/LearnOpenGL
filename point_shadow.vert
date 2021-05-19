#version 330 core;
layout(location = 0) in vec3 aPos;
layout(location = 1)in vec3 aNormal;
layout(location = 2)in vec2 aTexture;
layout(std140) uniform Matrices{
    mat4 aView;
    mat4 aProjection;
};
out VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
}vs_out;

uniform mat4 aModel;

void main(void)
{
    vs_out.FragPos = vec3(aModel * vec4(aPos,1.0));
    vs_out.Normal = transpose(inverse(mat3(aModel))) * aNormal;
    vs_out.TexCoords = aTexture;
    gl_Position = aProjection * aView * aModel * vec4(aPos,1.0);
}
