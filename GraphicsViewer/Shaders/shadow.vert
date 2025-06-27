#version 330

layout (location = 0) in vec3 inPosition;

uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorldTransform;

void main()
{
	gl_Position = uProjection * uView * uWorldTransform * vec4(inPosition, 1.0);
}