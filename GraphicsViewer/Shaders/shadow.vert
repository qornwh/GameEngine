#version 330 core

layout (location = 0) in vec3 inPosition;

uniform mat4 uLightSpaceMatrix;
uniform mat4 uWorldTransform;

void main()
{
	gl_Position = uLightSpaceMatrix * uWorldTransform * vec4(inPosition, 1.0);
}