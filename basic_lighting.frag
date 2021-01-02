#version 330 core
uniform vec3 lampColor;
uniform vec3 objColor;
uniform vec3 viewPosition;
uniform vec3 lightPosition;

in vec3 fragPos;
in vec3 normal;
out vec4 FragColor;

void main(void)
{
    // embition color;
    float ambientStrength = 0.1;
    vec3  embition = ambientStrength * lampColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(norm, lightDir),0.0f);
    vec3 diffuse = diff * lampColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - fragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = specularStrength * spec * lampColor;
    FragColor = vec4((embition + diffuse + specular) * objColor,1.0);
}
