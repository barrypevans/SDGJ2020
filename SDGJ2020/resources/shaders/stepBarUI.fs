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

	float miniT = (min(1,max(0,1-userData1)) - 0.1) / ( 0 - 0.1);
	vec3 BackColor = mix(vec3(0.06,  0.56, 0.39), vec3(1.0,  0.07, 0.33), 1- min(1,max(0,miniT)));

	vec3 FillColor = vec3(0.10, 0.01, 0.22);

	vec3 LerpColor = mix(BackColor,FillColor,StepColor);

	FragColor = vec4(LerpColor, TexColor.a);
}