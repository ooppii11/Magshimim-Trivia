#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername();
	bool operator==(const LoggedUser& user);
	bool operator<(const LoggedUser& user);
private:
	std::string _username;
	friend struct std::less<LoggedUser>;


};


namespace std
{
	template<> struct less<LoggedUser>
	{
		bool operator() (const LoggedUser& lhs, const LoggedUser& rhs) const
		{
			return lhs._username < rhs._username;
		}
	};
}