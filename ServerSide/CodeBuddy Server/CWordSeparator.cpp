#include "CWordSeparator.h"
#include <sstream>

std::vector<std::string> CWordSeparator::SeparateWords(std::string source, char delim)
{
    std::istringstream ss(source);
    std::vector<std::string> output;
    std::string token{};
    while (std::getline(ss, token, delim))
    {
        output.push_back(token);
    }

    return output;
}

std::string CWordSeparator::encapsulateWords(std::vector<std::vector<std::string>> words, int index, char delim)
{
    std::string buffer{};
    for (const auto& it : words)
    {
        buffer += it[index];
        buffer += delim;
    }
    return buffer;
}

std::string CWordSeparator::encapsulateWords(std::vector<std::string> words, char delim)
{
    std::string buffer{};
    for (const auto& it : words)
    {
        buffer += it;
        buffer += delim;
    }
    return buffer;
}

