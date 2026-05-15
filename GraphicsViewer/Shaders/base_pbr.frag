#version 330 core

in vec2 fragTexCoord;
in vec3 fragWorldPosition;
in vec3 fragNormal;

struct Material
{
	bool IsDeffuse;
	bool IsMetallic;
	bool IsRoughness;
	bool IsNormal;
	bool IsAO;
	bool IsEmissive;

	sampler2D deffuse;
	sampler2D metallic;
	sampler2D roughness;
	sampler2D normal;
	sampler2D ao;
	sampler2D emissive;
};

uniform Material uMaterial;

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
}