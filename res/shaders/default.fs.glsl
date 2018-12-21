#version 150 core

in vec4 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, Texcoord);
    outColor      = texColor * Color;
}

