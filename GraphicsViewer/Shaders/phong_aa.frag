#version 330

in vec2 fragTexCoord;
// 그림자
uniform sampler2D uShadow;
// 컬러 버퍼에 색출력
out vec4 outColor;

void main() 
{
    float depthValue = texture(uShadow, fragTexCoord).r;
    outColor = vec4(vec3(depthValue), 1.0);
}