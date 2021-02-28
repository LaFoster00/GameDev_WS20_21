#pragma once
#include <unordered_map>

class Shader;

enum class ShaderUniformType
{
	VEC1 = 0,
	VEC2 = 1,
	VEC3 = 2,
	VEC4 = 3,
	TEXTURE = 4,
};

struct ShaderUniform
{
	std::string name;
	uint32_t position;	
	ShaderUniformType type;
	void* data;
};

class Material
{
public:
	Material(Shader* shader);

	void SetUnifrom(uint32_t id, void* value);
	uint32_t SetUniform(const char* name, void* value, const ShaderUniformType& type);

	void PrepareForRender();

public:
	Shader* shader;
private:
	void SetShaderUniform(ShaderUniform& uniform);
	
	std::unordered_map<uint32_t, ShaderUniform> uniforms;
	std::unordered_map<const char*, uint32_t> uniformPositions;
};
