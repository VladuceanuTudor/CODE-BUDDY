#pragma once
#include <string>
#include <vector>

class CWordSeparator
{
private:

public:
	static std::vector<std::string> SeparateWords(std::string source, char delim);
};

