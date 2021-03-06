#pragma once
#include "Colour.h"
#include <string>
//Class holding methods whose implementation depends on the operating system.
class SystemMethods
{
public:
	//Convert a wide string to a string using ANSI format.
	virtual std::string ToString(const std::wstring& wstringToConvert) = 0;
	//Convert a string to a wide string using ANSI format.
	virtual std::wstring ToWString(const std::string& stringToConvert) = 0;
	//Converts a float to a wide string.
	virtual std::wstring ToWString(const float& floatToConvert, int numberOfDecimals = 5) = 0;
	//Converts a double to a wide string.
	static std::wstring ToWString(long double doubleToConvert, int numberOfDecimals);
	//Converts an UTF8 string to an ANSI wide string.
	static std::wstring UTF8ToWstring(const char *utf8ToConvert);
	//Converts a string to a bool.
	static bool ToBool(const std::string& stringToConvert);
	//Adds a string to the end of the filename, before the extension.
	virtual std::wstring AddToEndOfFilename(std::wstring originalFilename, std::wstring addition) = 0;
	//Gets the full path to the parent folder of the current running executable file (.exe in Windows).
	virtual std::wstring GetPathToExeParentDirectory() = 0;
	//Gets the full path to the current running executable file (.exe in Windows).
	virtual std::wstring GetPathToExeFile() = 0;
	//Gets the fiulkname of the current running executable file (.exe in Windows).
	virtual std::wstring GetExeFileName() = 0;
};
