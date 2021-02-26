#include "Rendering/Shader.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include "DebugTools.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


Shader::Shader(const std::string& filepath)
{
	m_filepath = filepath;
	ShaderProgramSource source = ParseShader(filepath);
	m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLASSERTCALL(glDeleteProgram(m_rendererID));
}

void Shader::Bind() const
{
	GLASSERTCALL(glUseProgram(m_rendererID));
}

void Shader::Unbind() const
{
	GLASSERTCALL(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLASSERTCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLASSERTCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				//set mode to vertex
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

#ifdef DEBUG_ENGINE
	std::cout << "Vertex Shader Code:" << std::endl << std::endl;
	std::cout << ss[0].str() << std::endl;
	std::cout << "Fragment Shader Code:" << std::endl << std::endl;
	std::cout << ss[1].str() << std::endl;
#endif

	return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
	GLASSERTCALL(uint32_t id = glCreateShader(type));
	const char* src = source.c_str();
	GLASSERTCALL(glShaderSource(id, 1, &src, nullptr));
	GLASSERTCALL(glCompileShader(id));

	int result;
	GLASSERTCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLASSERTCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = static_cast<char*>(alloca(length * sizeof(char)));
		GLASSERTCALL(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;

		GLASSERTCALL(glDeleteShader(id));
		return 0;
	}

	return id;
}

uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLASSERTCALL(uint32_t program = glCreateProgram());
	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLASSERTCALL(glAttachShader(program, vs));
	GLASSERTCALL(glAttachShader(program, fs));
	GLASSERTCALL(glLinkProgram(program));
	GLASSERTCALL(glValidateProgram(program));

	GLASSERTCALL(glDeleteShader(vs));
	GLASSERTCALL(glDeleteShader(fs));

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLASSERTCALL(uint32_t location = glGetUniformLocation(m_rendererID, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}else
	{
		m_UniformLocationCache[name] = location;
	}
	return location;
}
