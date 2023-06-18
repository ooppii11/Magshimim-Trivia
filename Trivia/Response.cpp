#include "Response.h"
#include "iomanip"
std::ostream& operator<<(std::ostream& os, const PlayerResults& data)
{
	return os
		<< "{"
		<< "\"AverageAnswerTime\": " << std::fixed << data.averageAnswerTime << ", "
		<< "\"CorrectAnswerCount\": " << data.correctAnswerCount << ", "
		<< "\"Username\": " << data.username << ", "
		<< "\"WrongAnswerCount\": " << data.wrongAnswerCount
		<< "}";;
}
