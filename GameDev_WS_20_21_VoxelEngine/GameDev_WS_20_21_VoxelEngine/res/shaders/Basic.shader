#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 vertexColor;

void main()
{
	color = vec4(vertexColor.xyz, 1.0);
}