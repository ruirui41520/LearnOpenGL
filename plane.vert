#version 330 core
layout(location = 0) vec3 aPos;
layout(location = 1) vec3 aNormal;
layout(location = 3) vec2 aTexCoords;
layout(std = 140) uniform Matrices
{
    mat4 aView;
    mat4 aProjection;
};
uniform mat4 aModel;
out vec3 normal;
out vec2 texCoords;

void main(void)
{
    gl_Position = aProjection * aView * aModel *vec4(aPos,1.0f);
    normal = vec3(normalize(aModel * vec4(aNormal,0.0f)));
    texCoords = aTexCoords;
}
