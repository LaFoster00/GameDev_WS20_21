#include "Serialization/JsonArchive.h"

#include <fstream>
#include <iostream>

JsonOutputArchive::JsonOutputArchive(const std::string& filePath)
	: m_pCurrentJson(&m_root)
	, m_filePath(filePath)
{ }

JsonOutputArchive::~JsonOutputArchive()
{
	std::ofstream fileStream;
	fileStream.open(m_filePath, std::fstream::out);
	std::cout << m_root.dump() << std::endl;
	fileStream << m_root.dump(4);
	fileStream.flush();
	fileStream.close();
}

void JsonOutputArchive::Serialize(bool& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(uint8_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(int8_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(uint16_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(int16_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(uint32_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(int32_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(uint64_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(int64_t& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(float& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(double& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(std::string& value, const std::string& label)
{
	(*m_pCurrentJson)[label] = value;
}

void JsonOutputArchive::Serialize(ObjectInterface& value, const std::string& label)
{
	JSONType* oldJson = m_pCurrentJson;

	JSONType tileMapJson;
	m_pCurrentJson = &tileMapJson;

	value.SerializeObject(*this);

	(*oldJson)[label] = tileMapJson;
	m_pCurrentJson = oldJson;
}




JsonInputArchive::JsonInputArchive(const std::string& filePath)
	: m_pCurrentJson(&m_root)
{
	std::ifstream fileStream(filePath);
	fileStream >> m_root;
}

void JsonInputArchive::Serialize(bool& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<bool>();
}

void JsonInputArchive::Serialize(uint8_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<uint8_t>();
}

void JsonInputArchive::Serialize(int8_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<int8_t>();
}

void JsonInputArchive::Serialize(uint16_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<uint16_t>();
}

void JsonInputArchive::Serialize(int16_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<int16_t>();
}

void JsonInputArchive::Serialize(uint32_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<uint32_t>();
}

void JsonInputArchive::Serialize(int32_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<int32_t>();
}

void JsonInputArchive::Serialize(uint64_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<uint64_t>();
}

void JsonInputArchive::Serialize(int64_t& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<int64_t>();
}

void JsonInputArchive::Serialize(float& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<float>();
}

void JsonInputArchive::Serialize(double& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<double>();
}

void JsonInputArchive::Serialize(std::string& value, const std::string& label)
{
	value = (*m_pCurrentJson)[label].get<std::string>();
}

void JsonInputArchive::Serialize(ObjectInterface& value, const std::string& label)
{
	JSONType* oldJson = m_pCurrentJson;

	JSONType& tilemapJson = (*m_pCurrentJson)[label];
	m_pCurrentJson = &tilemapJson;

	value.SerializeObject(*this);

	m_pCurrentJson = oldJson;
}
