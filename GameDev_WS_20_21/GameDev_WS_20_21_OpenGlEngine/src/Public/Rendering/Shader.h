#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#include "DebugTools.h"

struct ShaderProgramSource;

enum class UniformType
{
	NONE = 0,
	INT1 = 1,
	VEC1 = 2,
	VEC2 = 3,
	VEC3 = 4,
	VEC4 = 5,
	MAT4 = 6,
	TEXTURE = 7,
};

struct ShaderUniform
{
	uint32_t location;
	UniformType engineType;
	GLenum glType;
	std::string name;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void GetShaderUniforms(uint32_t program);
	
	std::string GetFilepath() const;

	inline void Bind() const
	{
		GLASSERTCALL(glUseProgram(m_rendererID));
	}

	inline void Unbind() const
	{
		GLASSERTCALL(glUseProgram(0));
	}

	//Set uniforms via name
	inline void SetUniformSampler(const std::string& name, int slot)
	{
		SetUniform1i(name, slot);
	}

	inline void SetUniform1i(const std::string& name, int value)
	{
		GLASSERTCALL(glUniform1i(Uniforms[name].location, value));
	}

	inline void SetUniform1f(const std::string& name, const float value)
	{
		GLASSERTCALL(glUniform1f(Uniforms[name].location, value));
	}

	inline void SetUniform2f(const std::string& name, const glm::vec2& value)
	{
		GLASSERTCALL(glUniform2f(Uniforms[name].location, value.x, value.y));
	}

	inline void SetUniform3f(const std::string& name, const glm::vec3& value)
	{
		GLASSERTCALL(glUniform3f(Uniforms[name].location, value.x, value.y, value.z));
	}

	inline void SetUniform4f(const std::string& name, const glm::vec4& value)
	{
		GLASSERTCALL(glUniform4f(Uniforms[name].location, value.x, value.y, value.z, value.w));
	}

	inline void SetUniformMat4(const std::string& name, glm::mat4 value)
	{
		GLASSERTCALL(glUniformMatrix4fv(Uniforms[name].location, 1, GL_FALSE, &value[0][0]));
	}

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	uint32_t CompileShader(uint32_t type, const std::string& source);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

public:
	std::unordered_map<std::string, ShaderUniform> Uniforms;
private:	
	uint32_t m_rendererID;
	std::string m_filepath;
};
