#include "Client.hpp"


Client::Client(std::string nickname, std::string username) : _nickname(nickname) , _username(username)
{
}

Client::Client(const Client &c) : _nickname(c._nickname), _username(c._username)
{

}

Client& Client::operator=(const Client& rhs)
{
	if (this != &rhs)
		*this = rhs;
	return(*this);

}

Client::~Client()
{
}