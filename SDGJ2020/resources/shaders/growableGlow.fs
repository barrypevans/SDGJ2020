#version 330 core

out vec4 FragColor;
in vec2 uv;
uniform float userData1;

uniform sampler2D colorTexture;

void main()
{
	vec4 TexColor = texture(colorTexture, uv);
	TexColor = (TexColor* vec4(1,0.67,0.14,1)) ;

	float alpha = (TexColor.a - (1-userData1)) / (1 - (1-userData1));

	FragColor = vec4(vec3(TexColor), alpha);
}