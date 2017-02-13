#version 330 
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tc;

uniform mat4 transform;

out vec2 texCoord;

void main()
{
	texCoord = tc;
	vec3 positionYChange = vec3(position.x, position.y + 4*sin(16 * 3.1415 * length(tc - vec2(0.5, 0.5))), position.z);
	gl_Position = transform * vec4(positionYChange, 1.0f);
}