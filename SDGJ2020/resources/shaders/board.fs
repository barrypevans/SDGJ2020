#version 330 core

out vec4 FragColor;
in vec2 uv;

uniform float userData1;
uniform sampler2D colorTexture;
uniform sampler2D userTexture;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}


vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    vec4 outColor = texture(colorTexture, uv);
    float mask = texture(userTexture, uv).r;

    if(mask > .5f)
    {
        vec3 outColorHsv = rgb2hsv(outColor.rgb);
        outColorHsv.x = outColorHsv.x + userData1*.25f;
        outColorHsv.yz = outColorHsv.yz *.8;
	    FragColor = vec4(hsv2rgb(outColorHsv) , outColor.a);
    }
    else
    {
        FragColor = outColor;
    }
}