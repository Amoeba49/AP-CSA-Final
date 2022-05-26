#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float time;

void main()
{
	FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0);
	//FragColor = vec4(abs(noise1(ourTime)), abs(cos(ourTime)), abs(tan(ourTime)), 1.0);
}