#pragma once
#include <iostream>
#include <unordered_map>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <nlohmann/json.hpp>

#include "Shader.h"

#define SETUNIFORM_EXPLICIT(type) \
public: \
template<> void SetUniform(const std::string& name, type value); \
private: \
template<> void SetShaderUniform(MaterialUniform<type>& uniform); \

class Shader;

template<typename T>
struct MaterialUniform
{
	ShaderUniform shaderUniform;
	T data;
};

class Material
{
public:
	Material(Shader* shader);

	void AllocateUniforms(Shader* shader);
	
	template<typename T>
	void SetUniform(const std::string& name, T value)
	{
		throw "Uniform type incompatible!";
	}
	
	void PrepareForRender();

	nlohmann::ordered_json Serialize()
	{
		nlohmann::ordered_json serializedMaterial;
		serializedMaterial["Shader"] = shader->GetFilepath();
		return serializedMaterial;
	}

private:

	template<typename T>
	void SetShaderUniform(MaterialUniform<T>& uniform)
	{
		throw "Uniform type incompatible!";
	}
public:
	Shader* shader;

private:	
	std::unordered_map<std::string, MaterialUniform<float>> floatUniforms;
	std::unordered_map<std::string, MaterialUniform<glm::vec2>> vec2Uniforms;
	std::unordered_map<std::string, MaterialUniform<glm::vec3>> vec3Uniforms;
	std::unordered_map<std::string, MaterialUniform<glm::vec4>> vec4Uniforms;
	std::unordered_map<std::string, MaterialUniform<glm::mat4>> mat4Uniforms;
	std::unordered_map<std::string, MaterialUniform<int>> intUniforms;

public:
	SETUNIFORM_EXPLICIT(float)
	SETUNIFORM_EXPLICIT(glm::vec2)
	SETUNIFORM_EXPLICIT(glm::vec3)
	SETUNIFORM_EXPLICIT(glm::vec4)
	SETUNIFORM_EXPLICIT(glm::mat4)
	SETUNIFORM_EXPLICIT(int)
};
