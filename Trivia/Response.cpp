#include "Response.h"

std::ostream& operator<<(std::ostream& os, const PlayerResults& data)
{
	return os
		<< "{"
		<< "\"AverageAnswerTime\": " << data.averageAnswerTime << ", "
		<< "\"correctAnswerCount\": " << data.correctAnswerCount << ", "
		<< "\"username\": " << data.username << ", "
		<< "\"wrongAnswerCount\": " << data.wrongAnswerCount
		<< "}";;
}
