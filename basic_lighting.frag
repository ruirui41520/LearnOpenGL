#version 330 core
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

struct Light{
    vec3 position;
    vec3 ambition;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;

};

uniform Light light;

uniform Matelier mateliar;

void main(void)
{
    float distance = length(light.position-fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                    light.quadratic * (distance * distance));

    // embition color;
    vec3  embition = light.ambition * texture(mateliar.diffuse,texCoords).rbg;
    embition *= attenuation;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir),0.0f);
    vec3 diffuse = diff* light.diffuse * texture(mateliar.diffuse,texCoords).rgb;
    diffuse *= attenuation;
    // specular
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0), mateliar.shininess);
    vec3 specular = spec * light.specular * texture(mateliar.specular,texCoords).rgb;
    specular *= attenuation;
    FragColor = vec4((embition + diffuse + specular) * objColor,1.0);
}
