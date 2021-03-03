#pragma once

#include "IArchive.h"
#include <nlohmann/json.hpp>

using JSONType = nlohmann::ordered_json;

class JsonOutputArchive : public IArchive
{

public:

	JsonOutputArchive(const std::string& filePath);
	~JsonOutputArchive();

	virtual bool IsInput() const override { return false; }
	virtual bool IsOutput() const override { return true; }

	virtual void Serialize(bool& value, const std::string& label) override;
	virtual void Serialize(uint8_t& value, const std::string& label) override;
	virtual void Serialize(int8_t& value, const std::string& label) override;
	virtual void Serialize(uint16_t& value, const std::string& label) override;
	virtual void Serialize(int16_t& value, const std::string& label) override;
	virtual void Serialize(uint32_t& value, const std::string& label) override;
	virtual void Serialize(int32_t& value, const std::string& label) override;
	virtual void Serialize(uint64_t& value, const std::string& label) override;
	virtual void Serialize(int64_t& value, const std::string& label) override;
	virtual void Serialize(float& value, const std::string& label) override;
	virtual void Serialize(double& value, const std::string& label) override;
	virtual void Serialize(std::string& value, const std::string& label) override;
	virtual void Serialize(ObjectInterface& value, const std::string& label) override;

private:

	std::string m_filePath;
	JSONType m_root;
	JSONType* m_pCurrentJson;
};

class JsonInputArchive : public IArchive
{
public:

	JsonInputArchive(const std::string& filePath);

	virtual bool IsInput() const override { return true; }
	virtual bool IsOutput() const override { return false; }

	virtual void Serialize(bool& value, const std::string& label) override;
	virtual void Serialize(uint8_t& value, const std::string& label) override;
	virtual void Serialize(int8_t& value, const std::string& label) override;
	virtual void Serialize(uint16_t& value, const std::string& label) override;
	virtual void Serialize(int16_t& value, const std::string& label) override;
	virtual void Serialize(uint32_t& value, const std::string& label) override;
	virtual void Serialize(int32_t& value, const std::string& label) override;
	virtual void Serialize(uint64_t& value, const std::string& label) override;
	virtual void Serialize(int64_t& value, const std::string& label) override;
	virtual void Serialize(float& value, const std::string& label) override;
	virtual void Serialize(double& value, const std::string& label) override;
	virtual void Serialize(std::string& value, const std::string& label) override;
	virtual void Serialize(ObjectInterface& value, const std::string& label) override;

private:

	JSONType m_root;
	JSONType* m_pCurrentJson;
};