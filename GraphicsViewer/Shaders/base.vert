#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uWorldTransform;
uniform mat4 uLightSpaceMatrix;

out vec3 fragWorldPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;
out vec4 fragLightSpacePosition;

void main() 
{
	fragWorldPosition = vec3(uWorldTransform * vec4(inPosition, 1.0));
	fragNormal = transpose(inverse(mat3(uWorldTransform))) * inNormal; // inNormal;
    fragTexCoord = inTexCoord;
	fragLightSpacePosition = uLightSpaceMatrix * vec4(fragWorldPosition, 1.0);

	gl_Position = uProjection * uView * uWorldTransform * vec4(inPosition, 1.0);
}