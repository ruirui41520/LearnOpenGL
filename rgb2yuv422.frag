#version 430 core
layout(local_size_x = 8, local_size_y = 8) in;
layout (binding = 1) uniform sampler2D outputImage;
layout (binding = 0) uniform sampler2D inputTexture;;
uniform float width;
uniform float height;

vec4 convertColor(in vec4 inputColor){
    vec3 offset = vec3(0.0625, 0.5, 0.5);
    vec3 ycoeff = vec3(0.256816, 0.504154, 0.0979137);
    vec3 ucoeff = vec3(0.439271, -0.367833, -0.071438);
    vec3 vcoeff = vec3(-0.148246, -0.29102, 0.439266);
    float y = dot(inputColor.rgb, ycoeff) += offset.x;
    float u = dot(inputColor.rgb, ucoeff) += offset.y;
    float v = dot(inputColor.rgb, vcoeff) += offset.z;
    return vec4(y,u,v,1.0f);
}

void main(void){
    vec2 position = ivec2(gl_GlobalInvocationID.xy);
    imageStore(outputImage,position,vec4(1.0f,0.0f,0.0f,1.0f));
//    imageStore(outputImage,position,convertColor(texture2D(inputTexture,position)));
}

