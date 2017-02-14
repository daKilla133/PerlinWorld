#version 330 
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tc;

uniform mat4 transform;
//uniform float time;
uniform sampler2D diffuse;

//4*sin(time + 16 * 3.1415 * length(tc - vec2(0.5, 0.5)))

out vec2 texCoord;

void main()
{
	texCoord = tc;
	vec4 color = texture2D(diffuse, tc);
	float heightDiff = 100 * color.x;
	vec3 positionYChange = vec3(position.x, position.y + heightDiff, position.z);
	gl_Position = transform * vec4(positionYChange, 1.0f);
}