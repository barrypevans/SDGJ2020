#version 330 core

out vec4 FragColor;
in vec2 uv;

uniform sampler2D colorTexture;

void main()
{
	FragColor = vec4(0,1,0,texture(colorTexture, uv).a);
}