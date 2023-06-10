#include "History.h"

std::ostream& operator<<(std::ostream& os, const History& data)
{
	//example:
	return os << "{" << "rank: " << data.rank << "}";;
}
