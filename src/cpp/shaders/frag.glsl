#version 330 core
layout(early_fragment_tests) in;
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float time;

void main()
{
	FragColor = texture(texture1, TexCoord);
	//FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0);
	//FragColor = vec4(abs(sin(time) * ourColor.x * 0.10), abs(cos(time) * ourColor.y * 0.10), abs(tan(time) * ourColor.z * 0.10), 1.0);
}