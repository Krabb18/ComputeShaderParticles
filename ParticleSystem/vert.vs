#version 430

layout (location = 0) in vec3 aPos; 

uniform mat4 camMat;

layout(std430, binding = 0) buffer DataBuffer {
    vec4 position[];
};

layout(std430, binding = 1) buffer DataBuffer2
{
	vec4 vel[];
};

layout(std430, binding = 2) buffer DataBuffer3
{
	vec4 scale[];
};

void main()
{
    vec4 pos = position[gl_InstanceID];
    vec3 finalPos = vec3(pos.x+aPos.x, pos.y+aPos.y, pos.z+aPos.z);
    gl_Position = camMat * vec4(finalPos, 1.0);
}