#pragma once

#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

struct ShaderProgramSource;

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniformMat4(const std::string& name, glm::mat4 value);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	uint32_t CompileShader(uint32_t type, const std::string& source);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
private:
	uint32_t m_rendererID;
	std::string m_filepath;
	std::unordered_map<std::string, uint32_t> m_UniformLocationCache;
};
