#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

#include "DebugTools.h"

struct ShaderProgramSource;

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

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
		SetUniform1iWithName(name, slot);
	}

	inline void SetUniform1iWithName(const std::string& name, int value)
	{
		GLASSERTCALL(glUniform1i(GetUniformLocation(name), value));
	}

	inline void SetUniform1fWithName(const std::string& name, const float value)
	{
		GLASSERTCALL(glUniform1f(GetUniformLocation(name), value));
	}

	inline void SetUniform2fWithName(const std::string& name, const glm::vec2& value)
	{
		GLASSERTCALL(glUniform2f(GetUniformLocation(name), value.x, value.y));
	}

	inline void SetUniform3fWithName(const std::string& name, const glm::vec3& value)
	{
		GLASSERTCALL(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
	}

	inline void SetUniform4fWithName(const std::string& name, const glm::vec4& value)
	{
		GLASSERTCALL(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
	}

	inline void SetUniformMat4WithName(const std::string& name, glm::mat4 value)
	{
		GLASSERTCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
	}

	// Set Uniforms via position
	inline void SetUniformSampler(uint32_t id, int slot)
	{
		SetUniform1i(id, slot);
	}

	inline void SetUniform1i(uint32_t id, int value)
	{
		GLASSERTCALL(glUniform1i(id, value));
	}

	inline void SetUniform1f(uint32_t id, const float value)
	{
		GLASSERTCALL(glUniform1f(id, value));
	}

	inline void SetUniform2f(uint32_t id, const glm::vec2& value)
	{
		GLASSERTCALL(glUniform2f(id, value.x, value.y));
	}

	inline void SetUniform3f(uint32_t id, const glm::vec3& value)
	{
		GLASSERTCALL(glUniform3f(id, value.x, value.y, value.z));
	}

	inline void SetUniform4f(uint32_t id, const glm::vec4& value)
	{
		GLASSERTCALL(glUniform4f(id, value.x, value.y, value.z, value.w));
	}

	inline void SetUniformMat4(uint32_t id, glm::mat4 value)
	{
		GLASSERTCALL(glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]));
	}

	int GetUniformLocation(const std::string& name);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	uint32_t CompileShader(uint32_t type, const std::string& source);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
	uint32_t m_rendererID;
	std::string m_filepath;
	std::unordered_map<std::string, uint32_t> m_UniformLocationCache;
};
