#version 330 core
out vec4 FragColor;
//in vec3 outColor;
in vec2 outTexcoor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, outTexcoor), texture(texture2, outTexcoor), 0.2);
}
