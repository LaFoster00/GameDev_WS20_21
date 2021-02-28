#include "Rendering/Material.h"

#include <iostream>

#include "Rendering/Shader.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
}

void Material::SetShaderUniform(ShaderUniform& uniform)
{
	switch (uniform.type)
	{
	case ShaderUniformType::VEC1:
		shader->SetUniform1f(uniform.position, *(float*)uniform.data);
		break;
	case ShaderUniformType::VEC2:
		shader->SetUniform2f(uniform.position, *(glm::vec2*)uniform.data);
		break;
	case ShaderUniformType::VEC3:
		shader->SetUniform3f(uniform.position, *(glm::vec3*)uniform.data);
		break;
	case ShaderUniformType::VEC4:
		shader->SetUniform4f(uniform.position, *(glm::vec4*)uniform.data);
		break;
	case ShaderUniformType::TEXTURE:
		shader->SetUniform1i(uniform.position, *(uint32_t*)uniform.data);
		break;
	}
}

void Material::SetUnifrom(uint32_t id, void* value)
{
	if (uniforms.find(id) == uniforms.end())
	{
		std::cout << "No parameter with id '" << id << "' found on shader" << std::endl;
	}

	ShaderUniform& uniform = uniforms[id];
	uniform.data = value;
}

uint32_t Material::SetUniform(const char* name, void* value, const ShaderUniformType& type)
{
	if (uniformPositions.find(name) == uniformPositions.end())
	{
		uint32_t uniformLocation = shader->GetUniformLocation(name);
		if (uniformLocation == -1) return 0;

		uniformPositions[name] = uniformLocation;
		uniforms[uniformLocation] = ShaderUniform();
		uniforms[uniformLocation].name = name;
		uniforms[uniformLocation].position = uniformLocation;
		uniforms[uniformLocation].type = type;
	}

	SetUnifrom(uniformPositions[name], value);
	return uniformPositions[name];
}

void Material::PrepareForRender()
{
	shader->Bind();

	for (auto uniform : uniforms)
	{
		SetShaderUniform(uniform.second);
	}
}
