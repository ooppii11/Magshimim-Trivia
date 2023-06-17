#include "Response.h"
#include "iomanip"
std::ostream& operator<<(std::ostream& os, const PlayerResults& data)
{
	return os
		<< "{"
		<< "\"AverageAnswerTime\": " << std::fixed << data.averageAnswerTime << ", "
		<< "\"correctAnswerCount\": " << data.correctAnswerCount << ", "
		<< "\"username\": " << data.username << ", "
		<< "\"wrongAnswerCount\": " << data.wrongAnswerCount
		<< "}";;
}
