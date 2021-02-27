#include "Rendering/Material.h"

#include <iostream>

#include "Rendering/Shader.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
}

void Material::SetUnifrom(uint32_t id, void* value)
{
	if (uniforms.find(id) == uniforms.end())
	{
		std::cout << "No parameter with id '" << id << "' found on shader" << std::endl;
	}

	ShaderUniform& uniform = uniforms[id];
	
	switch (uniform.type)
	{
		case ShaderUniformType::VEC1:
			shader->SetUniform1f(id, *(float*)uniform.data);
			break;
		case ShaderUniformType::VEC2:
			shader->SetUniform2f(id, *(glm::vec2*)uniform.data);
			break;
		case ShaderUniformType::VEC3:
			shader->SetUniform3f(id, *(glm::vec3*)uniform.data);
			break;
		case ShaderUniformType::VEC4:
			shader->SetUniform4f(id, *(glm::vec4*)uniform.data);
			break;
		case ShaderUniformType::TEXTURE:
			shader->SetUniform1f(id, *(uint32_t*)uniform.data);
			break;
	}
}

void Material::SetUniform(const char* name, void* value)
{
	if (uniformPositions.find(name) == uniformPositions.end())
	{
		uint32_t uniformLocation = shader->GetUniformLocation(name);
		if (uniformLocation == -1) return;

		uniformPositions[name] = uniformLocation;
	}

	SetUnifrom(uniformPositions[name], value);
}
