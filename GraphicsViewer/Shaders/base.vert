#version 330

// 세계변환
uniform mat4 uWorldTransform;
// 뷰포트 변환
uniform mat4 uView;
uniform mat4 uProjection;

// 속성 위치, 노말, uv
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec2 fragTexCoord;
out vec3 fragWorldPosition;
out vec3 fragNormal;

void main() 
{
	vec4 position = vec4(inPosition, 1.0);
	gl_Position = uProjection * uView * uWorldTransform * position;

    fragTexCoord = inTexCoord;
	fragWorldPosition = (uWorldTransform * position).xyz;
	fragNormal = inNormal;
}