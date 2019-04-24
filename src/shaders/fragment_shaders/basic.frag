#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float tex_mix;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
    FragColor = mix(texture(tex0, TexCoord), texture(tex1, TexCoord), tex_mix);
} 