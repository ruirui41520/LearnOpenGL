#version 330 core
out vec4 FragColor;
in vec3 TexCoords;
uniform samplerCube skybox;
in VS_OUT
{
    vec3 TexCoords;
} fs_in;

void main(void)
{
    FragColor = texture(skybox, fs_in.TexCoords);
}
