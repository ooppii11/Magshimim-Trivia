#pragma once
#include <iostream>
typedef struct History
{
	int categoryId;
	int rank;
	double avergeTime;
	int answers;
	int correctAnswers;
	time_t creationDate;
	friend std::ostream& operator<<(std::ostream& os, const History& data);
} History;