﻿#include "Rendering/Shader.h"

#include <fstream>
#include <sstream>


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

void Shader::GetShaderUniforms(uint32_t program)
{
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 32; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

	//printf("Active Uniforms: %d\n", count);

	for (i = 0; i < count; i++)
	{
		glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

		printf("Uniform #%d Type: %u Name: %s\n", i, type, name);

		UniformType engineType = UniformType::NONE;
		switch (type)
		{
			case GL_INT:
				engineType = UniformType::INT1;
				break;
			case GL_FLOAT:
				engineType = UniformType::VEC1;
				break;
			case GL_FLOAT_VEC2:
				engineType = UniformType::VEC2;
				break;
			case GL_FLOAT_VEC3:
				engineType = UniformType::VEC3;
				break;
			case GL_FLOAT_VEC4:
				engineType = UniformType::VEC4;
				break;
			case GL_SAMPLER_2D:
				engineType = UniformType::TEXTURE;
			break;
			case GL_FLOAT_MAT4:
				engineType = UniformType::MAT4;
			break;
		}

		if (engineType != UniformType::NONE)
		{
			ShaderUniform uniform{};
			uniform.location = i;
			uniform.engineType = engineType;
			uniform.glType = type;
			uniform.name = name;
			
			Uniforms[name] = uniform;
		}
	}
}

std::string Shader::GetFilepath() const
{
	return m_filepath;
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

	GetShaderUniforms(program);
	
	return program;
}