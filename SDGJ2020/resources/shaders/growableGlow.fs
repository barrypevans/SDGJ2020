#version 330 core

out vec4 FragColor;
in vec2 uv;
uniform float userData1;

uniform sampler2D colorTexture;

void main()
{
	vec4 TexColor = texture(colorTexture, uv);

	float alpha = (TexColor.a - userData1) / (1 - userData1);

	FragColor = vec4(vec3(TexColor), alpha);
}