#version 330 core
out vec4 FragColor;
in VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;
uniform sampler2D diffuseTexture;
uniform samplerCube depthCube;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool useShadows;

float ShadowCalculation(vec3 fragPos){
    vec3 lightToFrag = fragPos - lightPos ;
    float closestDepth = texture(depthCube, lightToFrag).r;
    closestDepth *= far_plane;
    float currentDepth = length(lightToFrag);
    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    return shadow;
}

void main(){
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
//    vec3 normal = normalize(fs_in.Normal);
//    vec3 lightColor = vec3(0.5);
//    vec3 ambition = 0.3 * lightColor;

//     vec3 lightDir =normalize(lightPos - fs_in.FragPos);
//     float diff = max(dot(lightDir , normal),0.0);
//     vec3 diffuse = diff * lightColor;

//     vec3 viewDir = normalize(viewPos - fs_in.FragPos);
//     vec3 reflectDir = reflect(-lightDir, normal);
//     vec3 halfwayDir = normalize(lightDir + viewDir);
//     float spec = pow(max(dot(normal , halfwayDir), 0.0), 64.0);
//     vec3 specular = spec * lightColor;

//     float shadow = useShadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
//     vec3 lighting = (ambition + (1.0 - shadow)*(diffuse + specular)) * color;
     FragColor = vec4(color, 1.0);
}
