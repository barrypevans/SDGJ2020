#version 330 core

out vec4 FragColor;
in vec2 uv;
uniform float animOffset;
uniform sampler2D colorTexture;

void main()
{
	vec2 offsetUv = uv + vec2(animOffset, 0);
	FragColor = texture(colorTexture, offsetUv);
}