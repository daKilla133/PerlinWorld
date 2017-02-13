#version 330 
precision highp float;

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D diffuse;
uniform vec4 color;
uniform int usingColor;

void main()
{
	if(usingColor == 1)
	{
		fragColor = color;
	}
	else
	{
		fragColor = texture2D(diffuse, texCoord);
	}
}