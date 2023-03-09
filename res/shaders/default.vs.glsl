#version 150

in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec4 Color;
out vec2 Texcoord;

uniform mat4 mvp;

void
main()
{
    Color    = color;
    Texcoord = texcoord;
    gl_Position = mvp * position;
}

