#version 330 
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tc;

uniform mat4 transform;

out vec2 texCoord;

void main()
{
	texCoord = tc;
	gl_Position = transform * vec4(position, 1.0f);
}