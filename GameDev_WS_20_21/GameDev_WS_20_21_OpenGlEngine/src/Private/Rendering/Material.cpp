#include "Rendering/Material.h"

#include <iostream>

#include "Rendering/Shader.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
	AllocateUniforms(shader);
}

void Material::AllocateUniforms(Shader* shader)
{
	for (auto uniform : shader->Uniforms)
	{
		switch (uniform.second.engineType)
		{
		case UniformType::VEC1:
			MaterialUniform<float> floatUniform;
			floatUniform.shaderUniform = uniform.second;
			floatUniform.data = 0;
			floatUniforms[uniform.second.name] = floatUniform;
			break;
		case UniformType::VEC2:
			MaterialUniform<glm::vec2> vec2Uniform;
			vec2Uniform.shaderUniform = uniform.second;
			vec2Uniform.data = glm::vec2(0);
			vec2Uniforms[uniform.second.name] = vec2Uniform;
			break;
		case UniformType::VEC3:
			MaterialUniform<glm::vec3> vec3Uniform;
			vec3Uniform.shaderUniform = uniform.second;
			vec3Uniform.data = glm::vec3(0);
			vec3Uniforms[uniform.second.name] = vec3Uniform;
			break;
		case UniformType::VEC4:
			MaterialUniform<glm::vec4> vec4Uniform;
			vec4Uniform.shaderUniform = uniform.second;
			vec4Uniform.data = glm::vec4(0);
			vec4Uniforms[uniform.second.name] = vec4Uniform;
			break;
		case UniformType::MAT4:
			MaterialUniform<glm::mat4> mat4Uniform;
			mat4Uniform.shaderUniform = uniform.second;
			mat4Uniform.data = glm::mat4(1);
			mat4Uniforms[uniform.second.name] = mat4Uniform;
		case UniformType::TEXTURE:
			MaterialUniform<int> textureUniform;
			textureUniform.shaderUniform = uniform.second;
			textureUniform.data = -1;
			intUniforms[uniform.second.name] = textureUniform;
			break;
		case UniformType::INT1:
			MaterialUniform<int> intUniform;
			intUniform.shaderUniform = uniform.second;
			intUniform.data = 0;
			intUniforms[uniform.second.name] = intUniform;
			break;
		}
	}
}

#define IMPLEMENT_SET_UNIFORM(dataType, mapName) \
template<> \
void Material::SetUniform(const char* name, dataType value)  \
{ \
	if (mapName##.find(name) == mapName##.end()) return; \
	mapName##[name].data = value; \
} \


IMPLEMENT_SET_UNIFORM(float, floatUniforms)

IMPLEMENT_SET_UNIFORM(glm::vec2,  vec2Uniforms)

IMPLEMENT_SET_UNIFORM(glm::vec3, vec3Uniforms)

IMPLEMENT_SET_UNIFORM(glm::vec4, vec4Uniforms)

IMPLEMENT_SET_UNIFORM(glm::mat4, mat4Uniforms)

IMPLEMENT_SET_UNIFORM(int, intUniforms)


template<>
void Material::SetShaderUniform(MaterialUniform<float>& uniform)
{
	shader->SetUniform1f(uniform.shaderUniform.name, uniform.data);
}

template<>
void Material::SetShaderUniform(MaterialUniform<glm::vec2>& uniform)
{
	shader->SetUniform2f(uniform.shaderUniform.name, uniform.data);
}

template<>
void Material::SetShaderUniform(MaterialUniform<glm::vec3>& uniform)
{
	shader->SetUniform3f(uniform.shaderUniform.name, uniform.data);
}

template<>
void Material::SetShaderUniform(MaterialUniform<glm::vec4> & uniform)
{
	shader->SetUniform4f(uniform.shaderUniform.name, uniform.data);
}

template<>
void Material::SetShaderUniform(MaterialUniform<glm::mat4>& uniform)
{
	shader->SetUniformMat4(uniform.shaderUniform.name, uniform.data);
}

template<>
void Material::SetShaderUniform(MaterialUniform<int>& uniform)
{
	shader->SetUniform1i(uniform.shaderUniform.name, uniform.data);
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
	for (auto uniform : intUniforms)
	{
		SetShaderUniform(uniform.second);
	}
}
