#include "History.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const History& data)
{
	return os 
		<< "{" 
		<< "\"CategoryName\": " << "\"\"" << ", " 
		<< "\"CategoryId\": " << data.categoryId << ", "
		<< "\"UserRank\": " << data.rank << ", "
		<< "\"CorrectAnswers\": " << data.correctAnswers << ", "
		<< "\"TotalAnswers\": " << data.answers << ", "
		<< "\"AvergeTime\": " << std::fixed << data.avergeTime << ","
		<< "\"CreationDate\": " << "\"" + data.creationDate + "\""
		<< "}";;
}
