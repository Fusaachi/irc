#include "Server.hpp"
class Client
{
private:
	std::string _nickname;
	std::string _username;
public:
	Client(std::string nickname, std::string username);
	Client(const Client &c);
	Client &operator=(const Client &rhs);
	~Client();
};


