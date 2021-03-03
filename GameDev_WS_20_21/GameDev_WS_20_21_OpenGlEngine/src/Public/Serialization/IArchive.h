#pragma once

#include <string>

#include "ObjectInterface.h"

struct IArchive
{
	virtual bool IsInput() const = 0;
	virtual bool IsOutput() const = 0;

	virtual void Serialize(bool& value, const std::string& label) = 0;
	virtual void Serialize(uint8_t& value, const std::string& label) = 0;
	virtual void Serialize(int8_t& value, const std::string& label) = 0;
	virtual void Serialize(uint16_t& value, const std::string& label) = 0;
	virtual void Serialize(int16_t& value, const std::string& label) = 0;
	virtual void Serialize(uint32_t& value, const std::string& label) = 0;
	virtual void Serialize(int32_t& value, const std::string& label) = 0;
	virtual void Serialize(uint64_t& value, const std::string& label) = 0;
	virtual void Serialize(int64_t& value, const std::string& label) = 0;
	virtual void Serialize(float& value, const std::string& label) = 0;
	virtual void Serialize(double& value, const std::string& label) = 0;
	virtual void Serialize(std::string& value, const std::string& label) = 0;
	virtual void Serialize(ObjectInterface& value, const std::string& label) = 0;

	template<typename T>
	void Serialize(T& value, const std::string& label)
	{
		ObjectInterface_Impl<T> objectInterfaceImpl(value);
		ObjectInterface& objectInterface = objectInterfaceImpl;
		Serialize(objectInterface, label);
	}

	template<typename T>
	void SerializeEnum(T& value, const std::string& label)
	{
		using EnumType = std::underlying_type<T>;
		EnumType integer = static_cast<EnumType>(value);
		Serialize(integer, label);
		value = static_cast<T>(integer);
	}
};