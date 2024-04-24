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
