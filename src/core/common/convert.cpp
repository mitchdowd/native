// Standard Dependencies
#include <cstdlib>
#include <cwchar>

// Module Dependencies
#include "../include/convert.h"
#include "../include/string.h"

namespace native
{
	int Convert::toInt(const String& str)
	{
		return toInt(str.toArray());
	}

	int Convert::toInt(const wchar_t* str)
	{
		return int(std::wcstol(str, nullptr, 10));
	}

	int Convert::toInt(const char* str)
	{
		return int(std::strtol(str, nullptr, 10));
	}

	float Convert::toFloat(const String& str)
	{
		return toFloat(str.toArray());
	}

	float Convert::toFloat(const wchar_t* str)
	{
		return float(std::wcstod(str, nullptr));
	}

	float Convert::toFloat(const char* str)
	{
		return float(std::strtod(str, nullptr));
	}
}

