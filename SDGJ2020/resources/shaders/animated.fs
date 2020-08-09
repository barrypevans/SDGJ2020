#version 330 core

out vec4 FragColor;
in vec2 uv;
uniform float curFrame;
uniform float numFrames;
uniform sampler2D colorTexture;

void main()
{
    
	vec2 offsetUv = (uv / vec2(numFrames,1)) + vec2(curFrame/numFrames,0);
	FragColor = texture(colorTexture, offsetUv);
}