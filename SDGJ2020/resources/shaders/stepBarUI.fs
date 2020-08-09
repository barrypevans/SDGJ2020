#version 330 core

out vec4 FragColor;
in vec2 uv;
uniform float userData1;

uniform sampler2D colorTexture;

void main()
{
	vec4 TexColor = texture(colorTexture, uv);
	float StepColor = (TexColor.r - userData1) / (0.1);
	//float StepColor = step(userData1, TexColor.r);

	vec3 BackColor = vec3(1.0,  0.07, 0.33);
	vec3 FillColor = vec3(0.10, 0.01, 0.22);

	vec3 LerpColor = mix(BackColor,FillColor,StepColor);

	FragColor = vec4(LerpColor, TexColor.a);
}