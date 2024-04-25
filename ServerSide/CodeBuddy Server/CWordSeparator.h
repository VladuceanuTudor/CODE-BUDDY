#pragma once
#include <string>
#include <vector>

class CWordSeparator
{
private:

public:
	static std::vector<std::string> SeparateWords(std::string source, char delim);
	static std::string encapsulateWords(std::vector<std::string> words, char delim);
	static std::string encapsulateWords(std::vector<std::vector<std::string>> words, int index, char delim);
};

