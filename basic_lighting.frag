#version 330 core
#define NR_POINT_LIGHTS 4
uniform vec3 lampColor;
uniform vec3 objColor;
uniform vec3 viewPosition;

in vec3 fragPos;
in vec3 normal;
out vec4 FragColor;
in vec2 texCoords;

struct Matelier{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;

};

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight pointLights[NR_POINT_LIGHTS];

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

uniform Matelier mateliar;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal,lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mateliar.shininess);
    // 合并结果
    vec3 ambient = light.ambient * vec3(texture(mateliar.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(mateliar.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(mateliar.specular, texCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mateliar.shininess);
    // 合并结果
    vec3 ambient = light.ambient * vec3(texture(mateliar.diffuse, texCoords));
    vec3 diffuse = light.diffuse * vec3(texture(mateliar.diffuse, texCoords));
    vec3 specular = light.specular * vec3(texture(mateliar.specular, texCoords));
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*distance*distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main(void)
{
    // diffuse
    vec3 norm = normalize(normal);
    // specular
    vec3 viewDir = normalize(viewPosition - fragPos);

    vec3 result = CalcDirLight(dirLight,norm,viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i],norm,fragPos,viewDir);

    FragColor = vec4(result, 1.0);
}
