#version 330 core

out vec4 FragColor;
in vec2 uv;
uniform float userData1;

uniform sampler2D colorTexture;

void main()
{
	vec4 TexColor = texture(colorTexture, uv);
	float StepColor = step(userData1, TexColor.r);
	FragColor = vec4(StepColor,StepColor,StepColor,TexColor.a);
}