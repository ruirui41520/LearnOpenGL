#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexcoor;
//out vec3 outColor;
out vec2 outTexcoor;
//  uniform float vertexOffset;
//uniform mat4 amatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;
void main(){
//   gl_Position = vec4(aPos.x + vertexOffset, aPos.y, aPos.z, 1.0);
    gl_Position = projectMatrix* viewMatrix * modelMatrix * vec4(aPos, 1.0);
//    outColor = aColor;
    outTexcoor = aTexcoor;
}
