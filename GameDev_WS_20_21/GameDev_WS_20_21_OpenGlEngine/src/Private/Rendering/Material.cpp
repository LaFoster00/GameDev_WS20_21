#include "Rendering/Material.h"

#include <iostream>

#include "Rendering/Shader.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
}

#define IMPLEMENT_SET_UNIFORM(dataType, uniformType, mapName) \
	template<> \
void Material::SetUniformWithId(uint32_t id, dataType value)  \
{ \
if (mapName.find(id) == mapName.end()) \
{ \
std::cout << "No parameter with id '" << id << "' found on shader" << std::endl; \
return; \
} \
ShaderUniform<dataType>& uniform = mapName[id]; \
uniform.data = value; \
} \
 \
template<> \
uint32_t Material::SetUniform(const char* name, dataType value)  \
{ \
	uint32_t uniformLocation = shader->GetUniformLocation(name); \
	if (uniformLocation == -1) return 0; \
 \
	uniformPositions[name] = uniformLocation; \
	 \
	std::unordered_map<uint32_t, ShaderUniform<dataType>>& uniforms = mapName; \
	uniforms[uniformLocation] = ShaderUniform<dataType>(); \
	uniforms[uniformLocation].position = uniformLocation; \
	uniforms[uniformLocation].data = value; \
	uniforms[uniformLocation].type = uniformType; \
	uniformTypes[uniformLocation] = uniformType; \
 \
	SetUniformWithId(uniformPositions[name], value); \
	return uniformPositions[name]; \
} \


IMPLEMENT_SET_UNIFORM(float, ShaderUniformType::VEC1, floatUniforms)

IMPLEMENT_SET_UNIFORM(glm::vec2, ShaderUniformType::VEC2, vec2Uniforms)

IMPLEMENT_SET_UNIFORM(glm::vec3, ShaderUniformType::VEC3, vec3Uniforms)

IMPLEMENT_SET_UNIFORM(glm::vec4, ShaderUniformType::VEC4, vec4Uniforms)

IMPLEMENT_SET_UNIFORM(glm::mat4, ShaderUniformType::MAT4, mat4Uniforms)

IMPLEMENT_SET_UNIFORM(uint32_t, ShaderUniformType::TEXTURE, uintUniforms)


template<>
void Material::SetShaderUniform(ShaderUniform<float>& uniform)
{
	shader->SetUniform1f(uniform.position, uniform.data);
}

template<>
void Material::SetShaderUniform(ShaderUniform<glm::vec2>& uniform)
{
	shader->SetUniform2f(uniform.position, uniform.data);
}

template<>
void Material::SetShaderUniform(ShaderUniform<glm::vec3>& uniform)
{
	shader->SetUniform3f(uniform.position, uniform.data);
}

template<>
void Material::SetShaderUniform(ShaderUniform<glm::vec4> & uniform)
{
	shader->SetUniform4f(uniform.position, uniform.data);
}

template<>
void Material::SetShaderUniform(ShaderUniform<glm::mat4>& uniform)
{
	shader->SetUniformMat4(uniform.position, uniform.data);
}

template<>
void Material::SetShaderUniform(ShaderUniform<uint32_t>& uniform)
{
	shader->SetUniform1i(uniform.position, uniform.data);
}


void Material::PrepareForRender()
{
	shader->Bind();

	for (auto uniform : floatUniforms)
	{
		SetShaderUniform(uniform.second);
	}
	for (auto uniform : vec2Uniforms)
	{
		SetShaderUniform(uniform.second);
	}
	for (auto uniform : vec3Uniforms)
	{
		SetShaderUniform(uniform.second);
	}
	for (auto uniform : vec4Uniforms)
	{
		SetShaderUniform(uniform.second);
	}
	for (auto uniform : mat4Uniforms)
	{
		SetShaderUniform(uniform.second);
	}
	for (auto uniform : uintUniforms)
	{
		SetShaderUniform(uniform.second);
	}
}
