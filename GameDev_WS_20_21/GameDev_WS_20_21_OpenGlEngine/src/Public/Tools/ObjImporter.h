#pragma once
#include <string>

class Mesh;

namespace Tools
{
	Mesh* LoadObj(const std::string& filePath);
}