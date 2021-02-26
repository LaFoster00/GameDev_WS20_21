#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out VERTEXOUT{
	vec2 _TexCoord;
}vertexout;

void main()
{
	gl_Position = position;
	vertexout._TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in VERTEXOUT{
	vec2 _TexCoord;
}vertexout;

uniform vec4 vertexColor;
uniform sampler2D _Texture;

void main()
{
	vec4 texColor = texture(_Texture, vertexout._TexCoord);
	color = vec4(texColor.xyz, 1.0f);
}