#include <Server.hpp>


Server::Server(int port, std::string password) : _port(port), _password(password)
{

}

Server::Server(const Server& c)
{
	this->_password = c._password;
	this->_port = c._port;
}

Server &Server::operator=(const Server & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

Server::~Server()
{
}
