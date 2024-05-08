#include "CExercice.h"
#include <vector>
#include <string>
#include "CWordSeparator.h"
#include "Constraints.h"

ServerMessageContainer CExercice::getSendData()
{
	std::vector<std::string> buffer;
	buffer.push_back(std::string(1, this->type));
	buffer.push_back(this->question);
	for (const auto& it : this->answers)
		buffer.push_back(it);
	buffer.push_back(this->realAnswer);

	return ServerMessageContainer(GET_EXERCICE_CODE, CWordSeparator::encapsulateWords(buffer, PAYLOAD_DELIM));
}