#pragma once
#include <iostream>
#include <unordered_map>
#include <vcruntime_typeinfo.h>
#include <glm/fwd.hpp>

#include "Shader.h"

#define SETUNIFORM_EXPLICIT(type) \
public: \
template<> void SetUniformWithId(uint32_t id, type value); \
template<> uint32_t SetUniform(const char* name, type value); \
private: \
template<> void SetShaderUniform(ShaderUniform<type>& uniform); \

enum class ShaderUniformType
{
	VEC1 = 0,
	VEC2 = 1,
	VEC3 = 2,
	VEC4 = 3,
	TEXTURE = 4,
	MAT4 = 5
};

template<typename T>
struct ShaderUniform
{
	std::string name;
	uint32_t position;
	ShaderUniformType type;
	T data;
};

class Material
{
public:
	Material(Shader* shader);

	template<typename T>
	void SetUniformWithId(uint32_t id, T value)
	{
		throw "This should not be called";
	}

	template<typename T>
	uint32_t SetUniform(const char* name, T value)
	{
		throw "This should not be called";
	}
	
	void PrepareForRender();
private:

	template<typename T>
	void SetShaderUniform(ShaderUniform<T>& uniform)
	{
		throw "This should't be called";
	}
public:
	Shader* shader;

private:	
	std::unordered_map<uint32_t, ShaderUniform<float>> floatUniforms;
	std::unordered_map<uint32_t, ShaderUniform<glm::vec2>> vec2Uniforms;
	std::unordered_map<uint32_t, ShaderUniform<glm::vec3>> vec3Uniforms;
	std::unordered_map<uint32_t, ShaderUniform<glm::vec4>> vec4Uniforms;
	std::unordered_map<uint32_t, ShaderUniform<glm::mat4>> mat4Uniforms;
	std::unordered_map<uint32_t, ShaderUniform<uint32_t>> uintUniforms;
	
	std::unordered_map<const char*, uint32_t> uniformPositions;
	std::unordered_map<uint32_t, ShaderUniformType> uniformTypes;

public:
	SETUNIFORM_EXPLICIT(float)
	SETUNIFORM_EXPLICIT(glm::vec2)
	SETUNIFORM_EXPLICIT(glm::vec3)
	SETUNIFORM_EXPLICIT(glm::vec4)
	SETUNIFORM_EXPLICIT(glm::mat4)
	SETUNIFORM_EXPLICIT(uint32_t)
};
