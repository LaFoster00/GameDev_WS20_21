#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out VERTEXOUT{
	vec2 _TexCoord;
	vec3 _Normal;
}vertOut;

uniform mat4 _MVP;

void main()
{
	gl_Position = _MVP * position;
	vertOut._TexCoord = texCoord;
	vertOut._Normal = normal;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in VERTEXOUT{
	vec2 _TexCoord;
	vec3 _Normal;
}fragIn;

uniform vec4 vertexColor;
uniform sampler2D _Texture;

void main()
{
	vec4 texColor = texture(_Texture, fragIn._TexCoord);
	color = vec4(1.0f);
}