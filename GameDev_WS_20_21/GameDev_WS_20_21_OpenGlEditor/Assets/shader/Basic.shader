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

	mat3 normalMatrix = mat3(_MVP);
	normalMatrix = inverse(normalMatrix);
	normalMatrix = transpose(normalMatrix);
	vertOut._Normal = normalize(normal * normalMatrix);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in VERTEXOUT{
	vec2 _TexCoord;
	vec3 _Normal;
}fragIn;

uniform vec4 vertexColor;
uniform sampler2D _Texture;

struct Lights
{
	vec3 position;
	vec3 diffuse; // Colour
};

float lambert(vec3 N, vec3 L)
{
	vec3 nrmN = normalize(N);
	vec3 nrmL = normalize(L);
	float result = dot(nrmN, nrmL);
	return max(result, 0.0);
}

void main()
{
	// Temporary light
	Lights light1;
	light1.position = vec3(2, 1, 4);
	light1.diffuse = vec3(1.0, 0.2, 1.0);

	Lights light2;
	light2.position = vec3(-3, -1, -4);
	light2.diffuse = vec3(0.2, 1.0, 1.0);

	Lights light3;
	light3.position = vec3(-3, -1, 3);
	light3.diffuse = vec3(1.0, 1.0, 0.2);

	vec3 color =light1.diffuse * lambert(fragIn._Normal, light1.position);
	color += light2.diffuse * lambert(fragIn._Normal, light2.position);
	color += light3.diffuse * lambert(fragIn._Normal, light3.position);
	color = max(texture(_Texture, fragIn._TexCoord).rgb * color, color);
		
	o_color = vec4(color.xyz, 1);
}