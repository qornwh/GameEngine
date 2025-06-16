#version 330

in vec2 fragTexCoord;
in vec3 fragWorldPosition;
in vec3 fragNormal;

// 텍스쳐
uniform sampler2D uTexture;

// 컬러 버퍼에 색출력
out vec4 outColor;

// 디렉셔널 라이트
struct DirectionalLight
{
	// 방향광
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	// 기본 세기
	float ambientStrength;
	float specularPow;
	float specularStrength;
};

uniform DirectionalLight uDirectLight;
uniform vec3 uCameraPosition;

void main() 
{
	// 물체 표면 벡터
	vec3 normal = normalize(fragNormal);
	// 빛 방향 벡터(반대)
	vec3 lightDir = normalize(-uDirectLight.direction);
	// 보이는 방향 
	vec3 viewDir = normalize(uCameraPosition - fragWorldPosition);
	// 빛 반사 방향
	vec3 reflectDir = normalize(reflect(-uDirectLight.direction, normal));

	// phong
	vec3 phong = uDirectLight.ambientStrength * uDirectLight.ambient;

	float nToLightDot = max(dot(normal, lightDir), 0.0); 
	if (nToLightDot > 0)
	{
		vec3 diffuse = nToLightDot * uDirectLight.diffuse;
		vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), uDirectLight.specularPow) * uDirectLight.specularStrength * uDirectLight.specular;
		phong += (diffuse + specular);
	}

	outColor = texture(uTexture, fragTexCoord) * vec4(phong, 1.0f);
}