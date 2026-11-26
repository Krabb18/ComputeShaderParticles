#version 430

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

void main()
{
    finalColor = vec4(0.5, 0.5, 0.5, 1.0);
}