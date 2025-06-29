#version 330 core

// uv
in vec2 fragTexCoord;

// 컬러 버퍼에 색출력
out vec4 outColor;

// 텍스쳐
uniform sampler2D uTexture;

void main() 
{
	outColor = texture(uTexture, fragTexCoord);
}